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
 int /*<<< orphan*/  EL_ANOMALY ; 
 TYPE_1__ Pico ; 
 int /*<<< orphan*/  SekPc ; 
 int /*<<< orphan*/  cpu68k_map_set (int /*<<< orphan*/ ,int,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  m68k_read16_map ; 
 int /*<<< orphan*/  m68k_read8_map ; 
 int realtec_bank ; 
 int realtec_size ; 

__attribute__((used)) static void carthw_realtec_write8(u32 a, u32 d)
{
	int i, bank_old = realtec_bank, size_old = realtec_size;

	if (a == 0x400000)
	{
		realtec_bank &= 0x0e0000;
		realtec_bank |= 0x300000 & (d << 19);
		if (realtec_bank != bank_old)
			elprintf(EL_ANOMALY, "write [%06x] %02x @ %06x", a, d, SekPc);
	}
	else if (a == 0x402000)
	{
		realtec_size = (d << 17) & 0x3e0000;
		if (realtec_size != size_old)
			elprintf(EL_ANOMALY, "write [%06x] %02x @ %06x", a, d, SekPc);
	}
	else if (a == 0x404000)
	{
		realtec_bank &= 0x300000;
		realtec_bank |= 0x0e0000 & (d << 17);
		if (realtec_bank != bank_old)
			elprintf(EL_ANOMALY, "write [%06x] %02x @ %06x", a, d, SekPc);
	}
	else
		elprintf(EL_ANOMALY, "realtec: unexpected write [%06x] %02x @ %06x", a, d, SekPc);

	if (realtec_bank >= 0 && realtec_size >= 0 &&
		(realtec_bank != bank_old || realtec_size != size_old))
	{
		elprintf(EL_ANOMALY, "realtec: new bank %06x, size %06x", realtec_bank, realtec_size, SekPc);
		if (realtec_size > Pico.romsize - realtec_bank)
		{
			elprintf(EL_ANOMALY, "realtec: bank too large / out of range?");
			return;
		}

		for (i = 0; i < 0x400000; i += realtec_size) {
			cpu68k_map_set(m68k_read8_map,  i, realtec_size - 1, Pico.rom + realtec_bank, 0);
			cpu68k_map_set(m68k_read16_map, i, realtec_size - 1, Pico.rom + realtec_bank, 0);
		}
	}
}