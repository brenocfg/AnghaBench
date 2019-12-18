#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sas_ha_struct {int num_phys; } ;
struct request {int resid_len; int /*<<< orphan*/  bio; } ;
struct Scsi_Host {TYPE_1__* hostt; } ;
struct TYPE_2__ {int* name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KM_USER0 ; 
 scalar_t__ PAGE_SIZE ; 
 int const SAS_EXPANDER_PRODUCT_ID_LEN ; 
 int const SAS_EXPANDER_VENDOR_ID_LEN ; 
 struct sas_ha_struct* SHOST_TO_SAS_HA (struct Scsi_Host*) ; 
#define  SMP_CONF_ROUTE_INFO 138 
#define  SMP_DISCOVER 137 
#define  SMP_PHY_CONTROL 136 
#define  SMP_PHY_TEST_FUNCTION 135 
#define  SMP_READ_GPIO_REG 134 
#define  SMP_REPORT_GENERAL 133 
#define  SMP_REPORT_MANUF_INFO 132 
#define  SMP_REPORT_PHY_ERR_LOG 131 
#define  SMP_REPORT_PHY_SATA 130 
#define  SMP_REPORT_ROUTE_INFO 129 
 int SMP_REQUEST ; 
 int SMP_RESPONSE ; 
 int SMP_RESP_FUNC_ACC ; 
 int SMP_RESP_FUNC_UNK ; 
 int SMP_RESP_INV_FRM_LEN ; 
#define  SMP_WRITE_GPIO_REG 128 
 int bio_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_page (int /*<<< orphan*/ ) ; 
 int const blk_rq_bytes (struct request*) ; 
 int /*<<< orphan*/  flush_kernel_dcache_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmap_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (int*,int /*<<< orphan*/ ) ; 
 int* kzalloc (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int const max (int const,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int*,...) ; 
 int /*<<< orphan*/  sas_host_smp_discover (struct sas_ha_struct*,int*,int) ; 
 int sas_host_smp_write_gpio (struct sas_ha_struct*,int*,int,int,int,int*) ; 
 int /*<<< orphan*/  sas_phy_control (struct sas_ha_struct*,int,int,int,int,int*) ; 
 int /*<<< orphan*/  sas_report_phy_sata (struct sas_ha_struct*,int*,int) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,struct Scsi_Host*,char*) ; 

int sas_smp_host_handler(struct Scsi_Host *shost, struct request *req,
			 struct request *rsp)
{
	u8 *req_data = NULL, *resp_data = NULL, *buf;
	struct sas_ha_struct *sas_ha = SHOST_TO_SAS_HA(shost);
	int error = -EINVAL;

	/* eight is the minimum size for request and response frames */
	if (blk_rq_bytes(req) < 8 || blk_rq_bytes(rsp) < 8)
		goto out;

	if (bio_offset(req->bio) + blk_rq_bytes(req) > PAGE_SIZE ||
	    bio_offset(rsp->bio) + blk_rq_bytes(rsp) > PAGE_SIZE) {
		shost_printk(KERN_ERR, shost,
			"SMP request/response frame crosses page boundary");
		goto out;
	}

	req_data = kzalloc(blk_rq_bytes(req), GFP_KERNEL);

	/* make sure frame can always be built ... we copy
	 * back only the requested length */
	resp_data = kzalloc(max(blk_rq_bytes(rsp), 128U), GFP_KERNEL);

	if (!req_data || !resp_data) {
		error = -ENOMEM;
		goto out;
	}

	local_irq_disable();
	buf = kmap_atomic(bio_page(req->bio), KM_USER0) + bio_offset(req->bio);
	memcpy(req_data, buf, blk_rq_bytes(req));
	kunmap_atomic(buf - bio_offset(req->bio), KM_USER0);
	local_irq_enable();

	if (req_data[0] != SMP_REQUEST)
		goto out;

	/* always succeeds ... even if we can't process the request
	 * the result is in the response frame */
	error = 0;

	/* set up default don't know response */
	resp_data[0] = SMP_RESPONSE;
	resp_data[1] = req_data[1];
	resp_data[2] = SMP_RESP_FUNC_UNK;

	switch (req_data[1]) {
	case SMP_REPORT_GENERAL:
		req->resid_len -= 8;
		rsp->resid_len -= 32;
		resp_data[2] = SMP_RESP_FUNC_ACC;
		resp_data[9] = sas_ha->num_phys;
		break;

	case SMP_REPORT_MANUF_INFO:
		req->resid_len -= 8;
		rsp->resid_len -= 64;
		resp_data[2] = SMP_RESP_FUNC_ACC;
		memcpy(resp_data + 12, shost->hostt->name,
		       SAS_EXPANDER_VENDOR_ID_LEN);
		memcpy(resp_data + 20, "libsas virt phy",
		       SAS_EXPANDER_PRODUCT_ID_LEN);
		break;

	case SMP_READ_GPIO_REG:
		/* FIXME: need GPIO support in the transport class */
		break;

	case SMP_DISCOVER:
		req->resid_len -= 16;
		if ((int)req->resid_len < 0) {
			req->resid_len = 0;
			error = -EINVAL;
			goto out;
		}
		rsp->resid_len -= 56;
		sas_host_smp_discover(sas_ha, resp_data, req_data[9]);
		break;

	case SMP_REPORT_PHY_ERR_LOG:
		/* FIXME: could implement this with additional
		 * libsas callbacks providing the HW supports it */
		break;

	case SMP_REPORT_PHY_SATA:
		req->resid_len -= 16;
		if ((int)req->resid_len < 0) {
			req->resid_len = 0;
			error = -EINVAL;
			goto out;
		}
		rsp->resid_len -= 60;
		sas_report_phy_sata(sas_ha, resp_data, req_data[9]);
		break;

	case SMP_REPORT_ROUTE_INFO:
		/* Can't implement; hosts have no routes */
		break;

	case SMP_WRITE_GPIO_REG: {
		/* SFF-8485 v0.7 */
		const int base_frame_size = 11;
		int to_write = req_data[4];

		if (blk_rq_bytes(req) < base_frame_size + to_write * 4 ||
		    req->resid_len < base_frame_size + to_write * 4) {
			resp_data[2] = SMP_RESP_INV_FRM_LEN;
			break;
		}

		to_write = sas_host_smp_write_gpio(sas_ha, resp_data, req_data[2],
						   req_data[3], to_write, &req_data[8]);
		req->resid_len -= base_frame_size + to_write * 4;
		rsp->resid_len -= 8;
		break;
	}

	case SMP_CONF_ROUTE_INFO:
		/* Can't implement; hosts have no routes */
		break;

	case SMP_PHY_CONTROL:
		req->resid_len -= 44;
		if ((int)req->resid_len < 0) {
			req->resid_len = 0;
			error = -EINVAL;
			goto out;
		}
		rsp->resid_len -= 8;
		sas_phy_control(sas_ha, req_data[9], req_data[10],
				req_data[32] >> 4, req_data[33] >> 4,
				resp_data);
		break;

	case SMP_PHY_TEST_FUNCTION:
		/* FIXME: should this be implemented? */
		break;

	default:
		/* probably a 2.0 function */
		break;
	}

	local_irq_disable();
	buf = kmap_atomic(bio_page(rsp->bio), KM_USER0) + bio_offset(rsp->bio);
	memcpy(buf, resp_data, blk_rq_bytes(rsp));
	flush_kernel_dcache_page(bio_page(rsp->bio));
	kunmap_atomic(buf - bio_offset(rsp->bio), KM_USER0);
	local_irq_enable();

 out:
	kfree(req_data);
	kfree(resp_data);
	return error;
}