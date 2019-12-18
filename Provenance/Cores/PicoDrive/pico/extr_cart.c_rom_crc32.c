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
struct TYPE_2__ {int /*<<< orphan*/  romsize; int /*<<< orphan*/  rom; } ;

/* Variables and functions */
 int /*<<< orphan*/  Byteswap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EL_STATUS ; 
 TYPE_1__ Pico ; 
 unsigned int crc32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static unsigned int rom_crc32(void)
{
  unsigned int crc;
  elprintf(EL_STATUS, "caclulating CRC32..");

  // have to unbyteswap for calculation..
  Byteswap(Pico.rom, Pico.rom, Pico.romsize);
  crc = crc32(0, Pico.rom, Pico.romsize);
  Byteswap(Pico.rom, Pico.rom, Pico.romsize);
  return crc;
}