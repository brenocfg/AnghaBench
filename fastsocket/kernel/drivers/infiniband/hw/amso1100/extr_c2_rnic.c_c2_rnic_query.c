#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union c2wr {int dummy; } c2wr ;
typedef  int u64 ;
struct ib_device_attr {int fw_ver; int max_mr_size; int page_size_cap; int vendor_id; int vendor_part_id; int hw_ver; int max_qp; int max_qp_wr; int max_cq; int max_cqe; int max_mr; int max_pd; int max_qp_rd_atom; int max_res_rd_atom; int max_qp_init_rd_atom; int max_mw; scalar_t__ local_ca_ack_delay; scalar_t__ max_pkeys; scalar_t__ max_srq_sge; scalar_t__ max_srq_wr; scalar_t__ max_srq; scalar_t__ max_map_per_fmr; scalar_t__ max_fmr; scalar_t__ max_ah; scalar_t__ max_total_mcast_qp_attach; scalar_t__ max_mcast_qp_attach; scalar_t__ max_mcast_grp; scalar_t__ max_raw_ethy_qp; scalar_t__ max_raw_ipv6_qp; scalar_t__ max_rdd; scalar_t__ max_ee; int /*<<< orphan*/  atomic_cap; scalar_t__ max_ee_init_rd_atom; scalar_t__ max_ee_rd_atom; int /*<<< orphan*/  max_sge_rd; int /*<<< orphan*/  max_sge; int /*<<< orphan*/  device_cap_flags; int /*<<< orphan*/  sys_image_guid; } ;
struct TYPE_3__ {unsigned long context; } ;
struct c2wr_rnic_query_req {int /*<<< orphan*/  rnic_handle; TYPE_1__ hdr; } ;
struct c2wr_rnic_query_rep {int /*<<< orphan*/  max_mws; int /*<<< orphan*/  max_qp_ord; int /*<<< orphan*/  max_global_ird; int /*<<< orphan*/  max_qp_ird; int /*<<< orphan*/  max_pds; int /*<<< orphan*/  max_mrs; int /*<<< orphan*/  max_cq_depth; int /*<<< orphan*/  max_cqs; int /*<<< orphan*/  max_qp_depth; int /*<<< orphan*/  max_qps; int /*<<< orphan*/  hw_version; int /*<<< orphan*/  part_number; int /*<<< orphan*/  vendor_id; int /*<<< orphan*/  fw_ver_patch; int /*<<< orphan*/  fw_ver_minor; int /*<<< orphan*/  fw_ver_major; } ;
struct c2_vq_req {scalar_t__ reply_msg; } ;
struct c2_dev {int /*<<< orphan*/  device_cap_flags; TYPE_2__* netdev; int /*<<< orphan*/  adapter_handle; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  C2_MAX_SGES ; 
 int /*<<< orphan*/  C2_MAX_SGE_RD ; 
 int C2_MIN_PAGESIZE ; 
 int /*<<< orphan*/  CCWR_RNIC_QUERY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IB_ATOMIC_NONE ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int c2_errno (struct c2wr_rnic_query_rep*) ; 
 int /*<<< orphan*/  c2_wr_set_id (struct c2wr_rnic_query_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vq_repbuf_free (struct c2_dev*,struct c2wr_rnic_query_rep*) ; 
 struct c2_vq_req* vq_req_alloc (struct c2_dev*) ; 
 int /*<<< orphan*/  vq_req_free (struct c2_dev*,struct c2_vq_req*) ; 
 int /*<<< orphan*/  vq_req_get (struct c2_dev*,struct c2_vq_req*) ; 
 int /*<<< orphan*/  vq_req_put (struct c2_dev*,struct c2_vq_req*) ; 
 int vq_send_wr (struct c2_dev*,union c2wr*) ; 
 int vq_wait_for_reply (struct c2_dev*,struct c2_vq_req*) ; 

__attribute__((used)) static int c2_rnic_query(struct c2_dev *c2dev, struct ib_device_attr *props)
{
	struct c2_vq_req *vq_req;
	struct c2wr_rnic_query_req wr;
	struct c2wr_rnic_query_rep *reply;
	int err;

	vq_req = vq_req_alloc(c2dev);
	if (!vq_req)
		return -ENOMEM;

	c2_wr_set_id(&wr, CCWR_RNIC_QUERY);
	wr.hdr.context = (unsigned long) vq_req;
	wr.rnic_handle = c2dev->adapter_handle;

	vq_req_get(c2dev, vq_req);

	err = vq_send_wr(c2dev, (union c2wr *) &wr);
	if (err) {
		vq_req_put(c2dev, vq_req);
		goto bail1;
	}

	err = vq_wait_for_reply(c2dev, vq_req);
	if (err)
		goto bail1;

	reply =
	    (struct c2wr_rnic_query_rep *) (unsigned long) (vq_req->reply_msg);
	if (!reply)
		err = -ENOMEM;
	else
		err = c2_errno(reply);
	if (err)
		goto bail2;

	props->fw_ver =
		((u64)be32_to_cpu(reply->fw_ver_major) << 32) |
		((be32_to_cpu(reply->fw_ver_minor) & 0xFFFF) << 16) |
		(be32_to_cpu(reply->fw_ver_patch) & 0xFFFF);
	memcpy(&props->sys_image_guid, c2dev->netdev->dev_addr, 6);
	props->max_mr_size         = 0xFFFFFFFF;
	props->page_size_cap       = ~(C2_MIN_PAGESIZE-1);
	props->vendor_id           = be32_to_cpu(reply->vendor_id);
	props->vendor_part_id      = be32_to_cpu(reply->part_number);
	props->hw_ver              = be32_to_cpu(reply->hw_version);
	props->max_qp              = be32_to_cpu(reply->max_qps);
	props->max_qp_wr           = be32_to_cpu(reply->max_qp_depth);
	props->device_cap_flags    = c2dev->device_cap_flags;
	props->max_sge             = C2_MAX_SGES;
	props->max_sge_rd          = C2_MAX_SGE_RD;
	props->max_cq              = be32_to_cpu(reply->max_cqs);
	props->max_cqe             = be32_to_cpu(reply->max_cq_depth);
	props->max_mr              = be32_to_cpu(reply->max_mrs);
	props->max_pd              = be32_to_cpu(reply->max_pds);
	props->max_qp_rd_atom      = be32_to_cpu(reply->max_qp_ird);
	props->max_ee_rd_atom      = 0;
	props->max_res_rd_atom     = be32_to_cpu(reply->max_global_ird);
	props->max_qp_init_rd_atom = be32_to_cpu(reply->max_qp_ord);
	props->max_ee_init_rd_atom = 0;
	props->atomic_cap          = IB_ATOMIC_NONE;
	props->max_ee              = 0;
	props->max_rdd             = 0;
	props->max_mw              = be32_to_cpu(reply->max_mws);
	props->max_raw_ipv6_qp     = 0;
	props->max_raw_ethy_qp     = 0;
	props->max_mcast_grp       = 0;
	props->max_mcast_qp_attach = 0;
	props->max_total_mcast_qp_attach = 0;
	props->max_ah              = 0;
	props->max_fmr             = 0;
	props->max_map_per_fmr     = 0;
	props->max_srq             = 0;
	props->max_srq_wr          = 0;
	props->max_srq_sge         = 0;
	props->max_pkeys           = 0;
	props->local_ca_ack_delay  = 0;

 bail2:
	vq_repbuf_free(c2dev, reply);

 bail1:
	vq_req_free(c2dev, vq_req);
	return err;
}