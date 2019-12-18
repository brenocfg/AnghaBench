#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct srp_target_port {int /*<<< orphan*/  qp; int /*<<< orphan*/  lkey; } ;
struct srp_iu {int /*<<< orphan*/  dma; } ;
struct ib_sge {int length; int /*<<< orphan*/  lkey; int /*<<< orphan*/  addr; } ;
struct ib_send_wr {uintptr_t wr_id; int num_sge; int /*<<< orphan*/  send_flags; int /*<<< orphan*/  opcode; struct ib_sge* sg_list; int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_SEND_SIGNALED ; 
 int /*<<< orphan*/  IB_WR_SEND ; 
 int ib_post_send (int /*<<< orphan*/ ,struct ib_send_wr*,struct ib_send_wr**) ; 

__attribute__((used)) static int srp_post_send(struct srp_target_port *target,
			 struct srp_iu *iu, int len)
{
	struct ib_sge list;
	struct ib_send_wr wr, *bad_wr;

	list.addr   = iu->dma;
	list.length = len;
	list.lkey   = target->lkey;

	wr.next       = NULL;
	wr.wr_id      = (uintptr_t) iu;
	wr.sg_list    = &list;
	wr.num_sge    = 1;
	wr.opcode     = IB_WR_SEND;
	wr.send_flags = IB_SEND_SIGNALED;

	return ib_post_send(target->qp, &wr, &bad_wr);
}