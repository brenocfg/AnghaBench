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
typedef  int u32 ;
struct TYPE_2__ {int romsize; scalar_t__ rom; } ;

/* Variables and functions */
 int EL_ANOMALY ; 
 int EL_STATUS ; 
 int M68K_BANK_MASK ; 
 TYPE_1__ Pico ; 
 int carthw_Xin1_baddr ; 
 int /*<<< orphan*/  cpu68k_map_set (int /*<<< orphan*/ ,int,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elprintf (int,char*,int) ; 
 int /*<<< orphan*/  m68k_read16_map ; 
 int /*<<< orphan*/  m68k_read8_map ; 

__attribute__((used)) static void carthw_Xin1_do(u32 a, int mask, int shift)
{
	int len;

	carthw_Xin1_baddr = a;
	a &= mask;
	a <<= shift;
	len = Pico.romsize - a;
	if (len <= 0) {
		elprintf(EL_ANOMALY|EL_STATUS, "X-in-1: missing bank @ %06x", a);
		return;
	}

	len = (len + M68K_BANK_MASK) & ~M68K_BANK_MASK;
	cpu68k_map_set(m68k_read8_map,  0x000000, len - 1, Pico.rom + a, 0);
	cpu68k_map_set(m68k_read16_map, 0x000000, len - 1, Pico.rom + a, 0);
}