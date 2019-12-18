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
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int REGULATOR_STATUS_NORMAL ; 
 int REGULATOR_STATUS_OFF ; 
 int REGULATOR_STATUS_STANDBY ; 
 int twl4030reg_grp (struct regulator_dev*) ; 

__attribute__((used)) static int twl4030reg_get_status(struct regulator_dev *rdev)
{
	int	state = twl4030reg_grp(rdev);

	if (state < 0)
		return state;
	state &= 0x0f;

	/* assume state != WARM_RESET; we'd not be running...  */
	if (!state)
		return REGULATOR_STATUS_OFF;
	return (state & BIT(3))
		? REGULATOR_STATUS_NORMAL
		: REGULATOR_STATUS_STANDBY;
}