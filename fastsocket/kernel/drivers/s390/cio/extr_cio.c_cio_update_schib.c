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
struct subchannel {int /*<<< orphan*/  schib; int /*<<< orphan*/  schid; } ;
struct schib {int dummy; } ;
typedef  int /*<<< orphan*/  schib ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  css_sch_is_valid (struct schib*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct schib*,int) ; 
 scalar_t__ stsch_err (int /*<<< orphan*/ ,struct schib*) ; 

int cio_update_schib(struct subchannel *sch)
{
	struct schib schib;

	if (stsch_err(sch->schid, &schib) || !css_sch_is_valid(&schib))
		return -ENODEV;

	memcpy(&sch->schib, &schib, sizeof(schib));
	return 0;
}