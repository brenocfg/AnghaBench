#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_3__ {int busreq; int stopwatch_base_c; } ;
struct TYPE_4__ {int* s68k_regs; TYPE_1__ m; int /*<<< orphan*/  bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_CDREG3 ; 
 int /*<<< orphan*/  EL_CDREGS ; 
 int /*<<< orphan*/  EL_UIO ; 
 TYPE_2__* Pico_mcd ; 
 int /*<<< orphan*/  SekCyclesDone () ; 
 int /*<<< orphan*/  SekPc ; 
 int cdc_host_r () ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  m68k_comm_check (int) ; 
 int pcd_cycles_m68k_to_s68k (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 m68k_reg_read16(u32 a)
{
  u32 d = 0;
  a &= 0x3e;

  switch (a) {
    case 0:
      // here IFL2 is always 0, just like in Gens
      d = ((Pico_mcd->s68k_regs[0x33] << 13) & 0x8000)
        | Pico_mcd->m.busreq;
      goto end;
    case 2:
      m68k_comm_check(a);
      d = (Pico_mcd->s68k_regs[a]<<8) | (Pico_mcd->s68k_regs[a+1]&0xc7);
      elprintf(EL_CDREG3, "m68k_regs r3: %02x @%06x", (u8)d, SekPc);
      goto end;
    case 4:
      d = Pico_mcd->s68k_regs[4]<<8;
      goto end;
    case 6:
      d = *(u16 *)(Pico_mcd->bios + 0x72);
      goto end;
    case 8:
      d = cdc_host_r();
      goto end;
    case 0xA:
      elprintf(EL_UIO, "m68k FIXME: reserved read");
      goto end;
    case 0xC: // 384 cycle stopwatch timer
      // ugh..
      d = pcd_cycles_m68k_to_s68k(SekCyclesDone());
      d = (d - Pico_mcd->m.stopwatch_base_c) / 384;
      d &= 0x0fff;
      elprintf(EL_CDREGS, "m68k stopwatch timer read (%04x)", d);
      goto end;
  }

  if (a < 0x30) {
    // comm flag/cmd/status (0xE-0x2F)
    m68k_comm_check(a);
    d = (Pico_mcd->s68k_regs[a]<<8) | Pico_mcd->s68k_regs[a+1];
    goto end;
  }

  elprintf(EL_UIO, "m68k_regs FIXME invalid read @ %02x", a);

end:
  return d;
}