#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {scalar_t__ dy; scalar_t__ dx; } ;
struct TYPE_5__ {scalar_t__ sm1; scalar_t__ sm2; } ;
struct hfsc_class {scalar_t__ cl_cumul; TYPE_1__ cl_deadline; void* cl_d; TYPE_1__ cl_eligible; void* cl_e; TYPE_3__ cl_rsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  eltree_insert (struct hfsc_class*) ; 
 int /*<<< orphan*/  psched_get_time () ; 
 int /*<<< orphan*/  rtsc_min (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 void* rtsc_y2x (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void
init_ed(struct hfsc_class *cl, unsigned int next_len)
{
	u64 cur_time = psched_get_time();

	/* update the deadline curve */
	rtsc_min(&cl->cl_deadline, &cl->cl_rsc, cur_time, cl->cl_cumul);

	/*
	 * update the eligible curve.
	 * for concave, it is equal to the deadline curve.
	 * for convex, it is a linear curve with slope m2.
	 */
	cl->cl_eligible = cl->cl_deadline;
	if (cl->cl_rsc.sm1 <= cl->cl_rsc.sm2) {
		cl->cl_eligible.dx = 0;
		cl->cl_eligible.dy = 0;
	}

	/* compute e and d */
	cl->cl_e = rtsc_y2x(&cl->cl_eligible, cl->cl_cumul);
	cl->cl_d = rtsc_y2x(&cl->cl_deadline, cl->cl_cumul + next_len);

	eltree_insert(cl);
}