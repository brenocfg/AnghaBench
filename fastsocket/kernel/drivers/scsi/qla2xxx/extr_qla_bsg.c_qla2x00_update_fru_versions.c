#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct qla_image_version_list {int /*<<< orphan*/  count; struct qla_image_version* version; } ;
struct TYPE_10__ {int /*<<< orphan*/  option; int /*<<< orphan*/  offset; int /*<<< orphan*/  device; } ;
struct qla_image_version {TYPE_2__ field_address; int /*<<< orphan*/  field_info; } ;
struct qla_hw_data {int /*<<< orphan*/  s_dma_pool; } ;
struct fc_bsg_reply {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  sg_cnt; int /*<<< orphan*/  sg_list; } ;
struct fc_bsg_job {int reply_len; int /*<<< orphan*/  (* job_done ) (struct fc_bsg_job*) ;TYPE_5__* reply; TYPE_1__ request_payload; struct Scsi_Host* shost; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_14__ {struct qla_hw_data* hw; } ;
typedef  TYPE_6__ scsi_qla_host_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  int /*<<< orphan*/  bsg ;
struct TYPE_11__ {scalar_t__* vendor_rsp; } ;
struct TYPE_12__ {TYPE_3__ vendor_reply; } ;
struct TYPE_13__ {int result; TYPE_4__ reply_data; } ;

/* Variables and functions */
 int DID_OK ; 
 int DMA_POOL_SIZE ; 
 scalar_t__ EXT_STATUS_MAILBOX ; 
 scalar_t__ EXT_STATUS_NO_MEMORY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 
 int qla2x00_write_sfp (TYPE_6__*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_copy_to_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qla_image_version_list*,int) ; 
 TYPE_6__* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  stub1 (struct fc_bsg_job*) ; 

__attribute__((used)) static int
qla2x00_update_fru_versions(struct fc_bsg_job *bsg_job)
{
	struct Scsi_Host *host = bsg_job->shost;
	scsi_qla_host_t *vha = shost_priv(host);
	struct qla_hw_data *ha = vha->hw;
	int rval = 0;
	uint8_t bsg[DMA_POOL_SIZE];
	struct qla_image_version_list *list = (void *)bsg;
	struct qla_image_version *image;
	uint32_t count;
	dma_addr_t sfp_dma;
	void *sfp = dma_pool_alloc(ha->s_dma_pool, GFP_KERNEL, &sfp_dma);
	if (!sfp) {
		bsg_job->reply->reply_data.vendor_reply.vendor_rsp[0] =
		    EXT_STATUS_NO_MEMORY;
		goto done;
	}

	sg_copy_to_buffer(bsg_job->request_payload.sg_list,
	    bsg_job->request_payload.sg_cnt, list, sizeof(bsg));

	image = list->version;
	count = list->count;
	while (count--) {
		memcpy(sfp, &image->field_info, sizeof(image->field_info));
		rval = qla2x00_write_sfp(vha, sfp_dma, sfp,
		    image->field_address.device, image->field_address.offset,
		    sizeof(image->field_info), image->field_address.option);
		if (rval) {
			bsg_job->reply->reply_data.vendor_reply.vendor_rsp[0] =
			    EXT_STATUS_MAILBOX;
			goto dealloc;
		}
		image++;
	}

	bsg_job->reply->reply_data.vendor_reply.vendor_rsp[0] = 0;

dealloc:
	dma_pool_free(ha->s_dma_pool, sfp, sfp_dma);

done:
	bsg_job->reply_len = sizeof(struct fc_bsg_reply);
	bsg_job->reply->result = DID_OK << 16;
	bsg_job->job_done(bsg_job);

	return 0;
}