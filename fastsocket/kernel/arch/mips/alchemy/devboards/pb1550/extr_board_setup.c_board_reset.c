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
 int BCSR_SYSTEM_RESET ; 
 int au_readw (int) ; 
 int /*<<< orphan*/  au_writew (int,int) ; 

void board_reset(void)
{
	/* Hit BCSR.SYSTEM[RESET] */
	au_writew(au_readw(0xAF00001C) & ~BCSR_SYSTEM_RESET, 0xAF00001C);
}