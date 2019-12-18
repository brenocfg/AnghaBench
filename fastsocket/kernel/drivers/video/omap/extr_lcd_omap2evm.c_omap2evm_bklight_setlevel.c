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
typedef  int u8 ;
struct lcd_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWL4030_MODULE_PWMA ; 
 int /*<<< orphan*/  TWL_PWMA_PWMAOFF ; 
 unsigned int bklight_level ; 
 int /*<<< orphan*/  twl4030_i2c_write_u8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap2evm_bklight_setlevel(struct lcd_panel *panel,
						unsigned int level)
{
	u8 c;
	if ((level >= 0) && (level <= 100)) {
		c = (125 * (100 - level)) / 100 + 2;
		twl4030_i2c_write_u8(TWL4030_MODULE_PWMA, c, TWL_PWMA_PWMAOFF);
		bklight_level = level;
	}
	return 0;
}