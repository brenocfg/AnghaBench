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
struct srp_iu {int /*<<< orphan*/  size; int /*<<< orphan*/  dma; } ;
struct ib_sge {int /*<<< orphan*/  lkey; int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct ib_recv_wr {uintptr_t wr_id; int num_sge; struct ib_sge* sg_list; int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 int ib_post_recv (int /*<<< orphan*/ ,struct ib_recv_wr*,struct ib_recv_wr**) ; 

__attribute__((used)) static int srp_post_recv(struct srp_target_port *target, struct srp_iu *iu)
{
	struct ib_recv_wr wr, *bad_wr;
	struct ib_sge list;

	list.addr   = iu->dma;
	list.length = iu->size;
	list.lkey   = target->lkey;

	wr.next     = NULL;
	wr.wr_id    = (uintptr_t) iu;
	wr.sg_list  = &list;
	wr.num_sge  = 1;

	return ib_post_recv(target->qp, &wr, &bad_wr);
}