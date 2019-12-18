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

/* Variables and functions */
 int /*<<< orphan*/  DISPC_CONTROL ; 
 int /*<<< orphan*/  MOD_REG_FLD (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void set_lcd_tft_mode(int enable)
{
	u32 mask;

	mask = 1 << 3;
	MOD_REG_FLD(DISPC_CONTROL, mask, enable ? mask : 0);
}