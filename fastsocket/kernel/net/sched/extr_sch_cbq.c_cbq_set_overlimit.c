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
struct tc_cbq_ovl {int strategy; int /*<<< orphan*/  penalty; int /*<<< orphan*/  priority2; } ;
struct cbq_class {int /*<<< orphan*/  penalty; int /*<<< orphan*/  overlimit; int /*<<< orphan*/  priority2; int /*<<< orphan*/  priority; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TC_CBQ_MAXPRIO ; 
#define  TC_CBQ_OVL_CLASSIC 132 
#define  TC_CBQ_OVL_DELAY 131 
#define  TC_CBQ_OVL_DROP 130 
#define  TC_CBQ_OVL_LOWPRIO 129 
#define  TC_CBQ_OVL_RCLASSIC 128 
 int /*<<< orphan*/  cbq_ovl_classic ; 
 int /*<<< orphan*/  cbq_ovl_delay ; 
 int /*<<< orphan*/  cbq_ovl_drop ; 
 int /*<<< orphan*/  cbq_ovl_lowprio ; 
 int /*<<< orphan*/  cbq_ovl_rclassic ; 

__attribute__((used)) static int cbq_set_overlimit(struct cbq_class *cl, struct tc_cbq_ovl *ovl)
{
	switch (ovl->strategy) {
	case TC_CBQ_OVL_CLASSIC:
		cl->overlimit = cbq_ovl_classic;
		break;
	case TC_CBQ_OVL_DELAY:
		cl->overlimit = cbq_ovl_delay;
		break;
	case TC_CBQ_OVL_LOWPRIO:
		if (ovl->priority2-1 >= TC_CBQ_MAXPRIO ||
		    ovl->priority2-1 <= cl->priority)
			return -EINVAL;
		cl->priority2 = ovl->priority2-1;
		cl->overlimit = cbq_ovl_lowprio;
		break;
	case TC_CBQ_OVL_DROP:
		cl->overlimit = cbq_ovl_drop;
		break;
	case TC_CBQ_OVL_RCLASSIC:
		cl->overlimit = cbq_ovl_rclassic;
		break;
	default:
		return -EINVAL;
	}
	cl->penalty = ovl->penalty;
	return 0;
}