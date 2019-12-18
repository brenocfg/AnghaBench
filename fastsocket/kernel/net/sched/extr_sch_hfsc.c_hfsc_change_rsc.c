#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct tc_service_curve {int dummy; } ;
struct TYPE_5__ {scalar_t__ dy; scalar_t__ dx; } ;
struct TYPE_4__ {scalar_t__ sm1; scalar_t__ sm2; } ;
struct hfsc_class {int /*<<< orphan*/  cl_flags; TYPE_2__ cl_eligible; TYPE_1__ cl_rsc; TYPE_2__ cl_deadline; int /*<<< orphan*/  cl_cumul; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFSC_RSC ; 
 int /*<<< orphan*/  rtsc_init (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc2isc (struct tc_service_curve*,TYPE_1__*) ; 

__attribute__((used)) static void
hfsc_change_rsc(struct hfsc_class *cl, struct tc_service_curve *rsc,
		u64 cur_time)
{
	sc2isc(rsc, &cl->cl_rsc);
	rtsc_init(&cl->cl_deadline, &cl->cl_rsc, cur_time, cl->cl_cumul);
	cl->cl_eligible = cl->cl_deadline;
	if (cl->cl_rsc.sm1 <= cl->cl_rsc.sm2) {
		cl->cl_eligible.dx = 0;
		cl->cl_eligible.dy = 0;
	}
	cl->cl_flags |= HFSC_RSC;
}