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
 int /*<<< orphan*/  PB1500_RST_VDDI ; 
 int /*<<< orphan*/  au_writel (int,int /*<<< orphan*/ ) ; 

void board_reset(void)
{
	/* Hit BCSR.RST_VDDI[SOFT_RESET] */
	au_writel(0x00000000, PB1500_RST_VDDI);
}