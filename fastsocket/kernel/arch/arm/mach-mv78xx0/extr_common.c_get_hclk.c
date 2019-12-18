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
 int /*<<< orphan*/  SAMPLE_AT_RESET_LOW ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_hclk(void)
{
	int hclk;

	/*
	 * HCLK tick rate is configured by DEV_D[7:5] pins.
	 */
	switch ((readl(SAMPLE_AT_RESET_LOW) >> 5) & 7) {
	case 0:
		hclk = 166666667;
		break;
	case 1:
		hclk = 200000000;
		break;
	case 2:
		hclk = 266666667;
		break;
	case 3:
		hclk = 333333333;
		break;
	case 4:
		hclk = 400000000;
		break;
	default:
		panic("unknown HCLK PLL setting: %.8x\n",
			readl(SAMPLE_AT_RESET_LOW));
	}

	return hclk;
}