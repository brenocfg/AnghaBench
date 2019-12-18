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
 int BBA_NCRA ; 
 int BBA_NCRA_RESET ; 
 int /*<<< orphan*/  bba_cmd_in8_slow (int) ; 
 int /*<<< orphan*/  bba_out8 (int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void __bba_reset()
{
	bba_out8(0x60,0x00);
	udelay(10000);
	bba_cmd_in8_slow(0x0F);
	udelay(10000);
	bba_out8(BBA_NCRA,BBA_NCRA_RESET);
	bba_out8(BBA_NCRA,0x00);
}