#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_3__ {unsigned int region_cnt; } ;
struct TYPE_4__ {TYPE_1__ mem_desc; } ;

/* Variables and functions */
 scalar_t__ const DISPC_GFX_ATTRIBUTES ; 
 scalar_t__ const DISPC_VID1_BASE ; 
 scalar_t__ const DISPC_VID2_BASE ; 
 scalar_t__ const DISPC_VID_ATTRIBUTES ; 
 int EINVAL ; 
 int /*<<< orphan*/  MOD_REG_FLD (scalar_t__ const,int,int) ; 
 TYPE_2__ dispc ; 
 int /*<<< orphan*/  enable_lcd_clocks (int) ; 

__attribute__((used)) static int omap_dispc_enable_plane(int plane, int enable)
{
	const u32 at_reg[] = { DISPC_GFX_ATTRIBUTES,
				DISPC_VID1_BASE + DISPC_VID_ATTRIBUTES,
				DISPC_VID2_BASE + DISPC_VID_ATTRIBUTES };
	if ((unsigned int)plane > dispc.mem_desc.region_cnt)
		return -EINVAL;

	enable_lcd_clocks(1);
	MOD_REG_FLD(at_reg[plane], 1, enable ? 1 : 0);
	enable_lcd_clocks(0);

	return 0;
}