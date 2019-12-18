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
struct twlreg_info {int dummy; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int P1_GRP ; 
 int /*<<< orphan*/  VREG_GRP ; 
 struct twlreg_info* rdev_get_drvdata (struct regulator_dev*) ; 
 int twl4030reg_read (struct twlreg_info*,int /*<<< orphan*/ ) ; 
 int twl4030reg_write (struct twlreg_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int twl4030reg_enable(struct regulator_dev *rdev)
{
	struct twlreg_info	*info = rdev_get_drvdata(rdev);
	int			grp;

	grp = twl4030reg_read(info, VREG_GRP);
	if (grp < 0)
		return grp;

	grp |= P1_GRP;
	return twl4030reg_write(info, VREG_GRP, grp);
}