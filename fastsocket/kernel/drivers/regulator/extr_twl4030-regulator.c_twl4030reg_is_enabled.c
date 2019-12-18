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
 int P1_GRP ; 
 int twl4030reg_grp (struct regulator_dev*) ; 

__attribute__((used)) static int twl4030reg_is_enabled(struct regulator_dev *rdev)
{
	int	state = twl4030reg_grp(rdev);

	if (state < 0)
		return state;

	return (state & P1_GRP) != 0;
}