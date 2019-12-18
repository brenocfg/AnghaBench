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
 int /*<<< orphan*/  MEMORY_CopyROM (int,int,scalar_t__) ; 
 int /*<<< orphan*/  MEMORY_dFillMem (int,int,int) ; 
 TYPE_1__* active_cart ; 

__attribute__((used)) static void set_bank_XEGS_8F_64(void)
{
	if (active_cart->state & 0x08)
		MEMORY_CopyROM(0x8000, 0x9fff, active_cart->image + (active_cart->state & ~0x08) * 0x2000);
	else
		/* $8000-$9FFF is left unconnected. */
		MEMORY_dFillMem(0x8000, 0xff, 0x2000);
}