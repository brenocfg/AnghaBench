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
struct vfpf_init_tlv {scalar_t__ sb_addr; int /*<<< orphan*/  stats_addr; int /*<<< orphan*/  spq_addr; } ;
struct bnx2x_virtf {int /*<<< orphan*/  op_rc; int /*<<< orphan*/  fw_stat_map; int /*<<< orphan*/  spq_map; } ;
struct bnx2x_vf_mbx {TYPE_2__* msg; } ;
struct bnx2x {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {struct vfpf_init_tlv init; } ;
struct TYPE_4__ {TYPE_1__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnx2x_vf_init (struct bnx2x*,struct bnx2x_virtf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnx2x_vf_mbx_resp (struct bnx2x*,struct bnx2x_virtf*) ; 

__attribute__((used)) static void bnx2x_vf_mbx_init_vf(struct bnx2x *bp, struct bnx2x_virtf *vf,
			      struct bnx2x_vf_mbx *mbx)
{
	struct vfpf_init_tlv *init = &mbx->msg->req.init;

	/* record ghost addresses from vf message */
	vf->spq_map = init->spq_addr;
	vf->fw_stat_map = init->stats_addr;
	vf->op_rc = bnx2x_vf_init(bp, vf, (dma_addr_t *)init->sb_addr);

	/* response */
	bnx2x_vf_mbx_resp(bp, vf);
}