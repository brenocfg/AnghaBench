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
struct radeon_cs_parser {int /*<<< orphan*/  dev; TYPE_1__* rdev; } ;
struct TYPE_2__ {scalar_t__ family; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 scalar_t__ CHIP_CAYMAN ; 
 int* cayman_reg_safe_bm ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,int) ; 
 int* evergreen_reg_safe_bm ; 

__attribute__((used)) static bool evergreen_is_safe_reg(struct radeon_cs_parser *p, u32 reg, u32 idx)
{
	u32 last_reg, m, i;

	if (p->rdev->family >= CHIP_CAYMAN)
		last_reg = ARRAY_SIZE(cayman_reg_safe_bm);
	else
		last_reg = ARRAY_SIZE(evergreen_reg_safe_bm);

	i = (reg >> 7);
	if (i >= last_reg) {
		dev_warn(p->dev, "forbidden register 0x%08x at %d\n", reg, idx);
		return false;
	}
	m = 1 << ((reg >> 2) & 31);
	if (p->rdev->family >= CHIP_CAYMAN) {
		if (!(cayman_reg_safe_bm[i] & m))
			return true;
	} else {
		if (!(evergreen_reg_safe_bm[i] & m))
			return true;
	}
	dev_warn(p->dev, "forbidden register 0x%08x at %d\n", reg, idx);
	return false;
}