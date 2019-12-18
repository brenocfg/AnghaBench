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
struct TYPE_2__ {scalar_t__ rom; scalar_t__ romsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_STATUS ; 
 TYPE_1__ Pico ; 
 int /*<<< orphan*/  PicoCartMemSetup ; 
 int PicoCartResize (scalar_t__) ; 
 int /*<<< orphan*/  carthw_prot_lk3_mem_setup ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 

void carthw_prot_lk3_startup(void)
{
  int ret;

  elprintf(EL_STATUS, "lk3 prot emu startup");

  // allocate space for bank0 backup
  ret = PicoCartResize(Pico.romsize + 0x8000);
  if (ret != 0) {
    elprintf(EL_STATUS, "OOM");
    return;
  }
  memcpy(Pico.rom + Pico.romsize, Pico.rom, 0x8000);

  PicoCartMemSetup = carthw_prot_lk3_mem_setup;
}