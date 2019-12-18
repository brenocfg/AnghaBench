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
struct matrox_hw_state {unsigned int* DACclk; } ;

/* Variables and functions */
#define  M_SYSTEM_PLL 128 

__attribute__((used)) static void updatehwstate_clk(struct matrox_hw_state* hw, unsigned int mnp, unsigned int pll) {
	switch (pll) {
		case M_SYSTEM_PLL:
			hw->DACclk[3] = mnp >> 16;
			hw->DACclk[4] = mnp >> 8;
			hw->DACclk[5] = mnp;
			break;
	}
}