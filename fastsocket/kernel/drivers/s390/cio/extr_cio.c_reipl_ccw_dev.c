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
struct ccw_dev_id {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  do_reipl_asm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ reipl_find_schid (struct ccw_dev_id*,struct subchannel_id*) ; 
 int /*<<< orphan*/  s390_reset_system (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void reipl_ccw_dev(struct ccw_dev_id *devid)
{
	struct subchannel_id schid;

	s390_reset_system(NULL, NULL);
	if (reipl_find_schid(devid, &schid) != 0)
		panic("IPL Device not found\n");
	do_reipl_asm(*((__u32*)&schid));
}