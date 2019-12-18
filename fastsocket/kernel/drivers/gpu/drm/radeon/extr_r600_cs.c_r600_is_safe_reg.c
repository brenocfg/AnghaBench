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
typedef  int u32 ;
struct radeon_cs_parser {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,int) ; 
 int* r600_reg_safe_bm ; 

__attribute__((used)) static bool r600_is_safe_reg(struct radeon_cs_parser *p, u32 reg, u32 idx)
{
	u32 m, i;

	i = (reg >> 7);
	if (i >= ARRAY_SIZE(r600_reg_safe_bm)) {
		dev_warn(p->dev, "forbidden register 0x%08x at %d\n", reg, idx);
		return false;
	}
	m = 1 << ((reg >> 2) & 31);
	if (!(r600_reg_safe_bm[i] & m))
		return true;
	dev_warn(p->dev, "forbidden register 0x%08x at %d\n", reg, idx);
	return false;
}