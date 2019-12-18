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
typedef  size_t u32 ;
struct cnic_local {int /*<<< orphan*/  fcoe_cid_tbl; int /*<<< orphan*/  cid_tbl; struct cnic_context* ctx_tbl; } ;
struct cnic_iscsi {int /*<<< orphan*/  task_array_info; int /*<<< orphan*/  r2tq_info; int /*<<< orphan*/  hq_info; } ;
struct cnic_dev {struct cnic_local* cnic_priv; } ;
struct TYPE_2__ {struct cnic_iscsi* iscsi; } ;
struct cnic_context {scalar_t__ ulp_proto_id; scalar_t__ cid; TYPE_1__ proto; } ;

/* Variables and functions */
 scalar_t__ CNIC_ULP_ISCSI ; 
 int /*<<< orphan*/  cnic_free_dma (struct cnic_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cnic_free_id (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void cnic_free_bnx2x_conn_resc(struct cnic_dev *dev, u32 l5_cid)
{
	struct cnic_local *cp = dev->cnic_priv;
	struct cnic_context *ctx = &cp->ctx_tbl[l5_cid];

	if (ctx->ulp_proto_id == CNIC_ULP_ISCSI) {
		struct cnic_iscsi *iscsi = ctx->proto.iscsi;

		cnic_free_dma(dev, &iscsi->hq_info);
		cnic_free_dma(dev, &iscsi->r2tq_info);
		cnic_free_dma(dev, &iscsi->task_array_info);
		cnic_free_id(&cp->cid_tbl, ctx->cid);
	} else {
		cnic_free_id(&cp->fcoe_cid_tbl, ctx->cid);
	}

	ctx->cid = 0;
}