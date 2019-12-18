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

/* Variables and functions */
 int /*<<< orphan*/  SAMPLE_AT_RESET_HIGH ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_tclk(void)
{
	int tclk;

	/*
	 * TCLK tick rate is configured by DEV_A[2:0] strap pins.
	 */
	switch ((readl(SAMPLE_AT_RESET_HIGH) >> 6) & 7) {
	case 1:
		tclk = 166666667;
		break;
	case 3:
		tclk = 200000000;
		break;
	default:
		panic("unknown TCLK PLL setting: %.8x\n",
			readl(SAMPLE_AT_RESET_HIGH));
	}

	return tclk;
}