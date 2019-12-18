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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  num_sge; } ;
struct qib_swqe {int psn; int length; TYPE_1__ wr; int /*<<< orphan*/ * sg_list; } ;
struct qib_sge_state {int total_len; int /*<<< orphan*/  num_sge; int /*<<< orphan*/ * sg_list; int /*<<< orphan*/  sge; } ;

/* Variables and functions */
 int QIB_PSN_MASK ; 
 int /*<<< orphan*/  qib_skip_sge (struct qib_sge_state*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 restart_sge(struct qib_sge_state *ss, struct qib_swqe *wqe,
		       u32 psn, u32 pmtu)
{
	u32 len;

	len = ((psn - wqe->psn) & QIB_PSN_MASK) * pmtu;
	ss->sge = wqe->sg_list[0];
	ss->sg_list = wqe->sg_list + 1;
	ss->num_sge = wqe->wr.num_sge;
	ss->total_len = wqe->length;
	qib_skip_sge(ss, len, 0);
	return wqe->length - len;
}