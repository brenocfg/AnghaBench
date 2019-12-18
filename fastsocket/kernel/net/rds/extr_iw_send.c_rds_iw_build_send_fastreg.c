#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_7__ {int length; int page_list_len; int /*<<< orphan*/  iova_start; int /*<<< orphan*/  access_flags; int /*<<< orphan*/  page_shift; TYPE_1__* page_list; int /*<<< orphan*/  rkey; } ;
struct TYPE_8__ {TYPE_2__ fast_reg; } ;
struct TYPE_9__ {TYPE_3__ wr; int /*<<< orphan*/  opcode; } ;
struct rds_iw_send_work {int /*<<< orphan*/  s_remap_count; TYPE_5__* s_mr; TYPE_4__ s_wr; TYPE_1__* s_page_list; } ;
struct rds_iw_device {int dummy; } ;
struct rds_iw_connection {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  rkey; } ;
struct TYPE_6__ {int max_page_list_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  IB_ACCESS_REMOTE_WRITE ; 
 int /*<<< orphan*/  IB_WR_FAST_REG_MR ; 
 int /*<<< orphan*/  PAGE_SHIFT ; 
 int /*<<< orphan*/  ib_update_fast_reg_key (TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rds_iw_build_send_fastreg(struct rds_iw_device *rds_iwdev, struct rds_iw_connection *ic, struct rds_iw_send_work *send, int nent, int len, u64 sg_addr)
{
	BUG_ON(nent > send->s_page_list->max_page_list_len);
	/*
	 * Perform a WR for the fast_reg_mr. Each individual page
	 * in the sg list is added to the fast reg page list and placed
	 * inside the fast_reg_mr WR.
	 */
	send->s_wr.opcode = IB_WR_FAST_REG_MR;
	send->s_wr.wr.fast_reg.length = len;
	send->s_wr.wr.fast_reg.rkey = send->s_mr->rkey;
	send->s_wr.wr.fast_reg.page_list = send->s_page_list;
	send->s_wr.wr.fast_reg.page_list_len = nent;
	send->s_wr.wr.fast_reg.page_shift = PAGE_SHIFT;
	send->s_wr.wr.fast_reg.access_flags = IB_ACCESS_REMOTE_WRITE;
	send->s_wr.wr.fast_reg.iova_start = sg_addr;

	ib_update_fast_reg_key(send->s_mr, send->s_remap_count++);
}