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
struct subchannel_id {int dummy; } ;
struct schib {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  css_schedule_eval (struct subchannel_id) ; 
 scalar_t__ stsch_err (struct subchannel_id,struct schib*) ; 

__attribute__((used)) static int s390_process_res_acc_new_sch(struct subchannel_id schid, void *data)
{
	struct schib schib;
	/*
	 * We don't know the device yet, but since a path
	 * may be available now to the device we'll have
	 * to do recognition again.
	 * Since we don't have any idea about which chpid
	 * that beast may be on we'll have to do a stsch
	 * on all devices, grr...
	 */
	if (stsch_err(schid, &schib))
		/* We're through */
		return -ENXIO;

	/* Put it on the slow path. */
	css_schedule_eval(schid);
	return 0;
}