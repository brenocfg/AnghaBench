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
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  MEMORY_SetRAM (int,int) ; 
 int /*<<< orphan*/  MEMORY_dFillMem (int,int,int) ; 
 scalar_t__ MEMORY_mem ; 
 int MEMORY_ram_size ; 
 scalar_t__ cart809F_enabled ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  under_cart809F ; 

void MEMORY_Cart809fDisable(void)
{
	if (cart809F_enabled) {
		if (MEMORY_ram_size > 32) {
			memcpy(MEMORY_mem + 0x8000, under_cart809F, 0x2000);
			MEMORY_SetRAM(0x8000, 0x9fff);
		}
		else
			MEMORY_dFillMem(0x8000, 0xff, 0x2000);
		cart809F_enabled = FALSE;
	}
}