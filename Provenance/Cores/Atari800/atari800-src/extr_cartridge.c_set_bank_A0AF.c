#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int state; scalar_t__ image; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEMORY_CartA0bfDisable () ; 
 int /*<<< orphan*/  MEMORY_CartA0bfEnable () ; 
 int /*<<< orphan*/  MEMORY_CopyROM (int,int,scalar_t__) ; 
 int /*<<< orphan*/  MEMORY_dFillMem (int,int,int) ; 
 TYPE_1__* active_cart ; 

__attribute__((used)) static void set_bank_A0AF(int main, int old_state)
{
	if (active_cart->state < 0)
		MEMORY_CartA0bfDisable();
	else {
		MEMORY_CartA0bfEnable();
		if (active_cart->state == 0xff)
			/* Fill cart area with 0xFF. */
			MEMORY_dFillMem(0xa000, 0xff, 0x1000);
		else
			MEMORY_CopyROM(0xa000, 0xafff, active_cart->image + active_cart->state * 0x1000);
		if (old_state < 0)
			MEMORY_CopyROM(0xb000, 0xbfff, active_cart->image + main);
	}
}