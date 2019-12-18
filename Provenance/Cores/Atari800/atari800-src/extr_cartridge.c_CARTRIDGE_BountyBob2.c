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
typedef  int UWORD ;
struct TYPE_2__ {int state; scalar_t__ image; } ;

/* Variables and functions */
 scalar_t__ Atari800_MACHINE_5200 ; 
 scalar_t__ Atari800_machine_type ; 
 int /*<<< orphan*/  MEMORY_CopyROM (int,int,scalar_t__) ; 
 TYPE_1__* active_cart ; 

void CARTRIDGE_BountyBob2(UWORD addr)
{
	if (Atari800_machine_type == Atari800_MACHINE_5200) {
		if (addr >= 0x5ff6 && addr <= 0x5ff9) {
			addr -= 0x5ff6;
			MEMORY_CopyROM(0x5000, 0x5fff, active_cart->image + 0x4000 + addr * 0x1000);
			active_cart->state = (active_cart->state & 0x03) | (addr << 2);
		}
	}
	else {
		if (addr >= 0x9ff6 && addr <= 0x9ff9) {
			addr -= 0x9ff6;
			MEMORY_CopyROM(0x9000, 0x9fff, active_cart->image + 0x4000 + addr * 0x1000);
			active_cart->state = (active_cart->state & 0x03) | (addr << 2);
		}
	}
}