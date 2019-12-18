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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_3__ {scalar_t__ m68k_poll_cnt; } ;
struct TYPE_4__ {int* s68k_regs; TYPE_1__ m; } ;

/* Variables and functions */
 TYPE_2__* Pico_mcd ; 
 int /*<<< orphan*/  SekEndRunS68k (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfx_start (int) ; 
 int /*<<< orphan*/  s68k_reg_write8 (int,int) ; 

void s68k_reg_write16(u32 a, u32 d)
{
  u8 *r = Pico_mcd->s68k_regs;

  if ((a & 0x1f0) == 0x20)
    goto write_comm;

  switch (a) {
    case 0x0e:
      // special case, 2 byte writes would be handled differently
      // TODO: verify
      r[0xf] = d;
      return;
    case 0x58: // stamp data size
      r[0x59] = d & 7;
      return;
    case 0x5a: // stamp map base address
      r[0x5a] = d >> 8;
      r[0x5b] = d & 0xe0;
      return;
    case 0x5c: // V cell size
      r[0x5d] = d & 0x1f;
      return;
    case 0x5e: // image buffer start address
      r[0x5e] = d >> 8;
      r[0x5f] = d & 0xf8;
      return;
    case 0x60: // image buffer offset
      r[0x61] = d & 0x3f;
      return;
    case 0x62: // h dot size
      r[0x62] = (d >> 8) & 1;
      r[0x63] = d;
      return;
    case 0x64: // v dot size
      r[0x65] = d;
      return;
    case 0x66: // trace vector base address
      d &= 0xfffe;
      r[0x66] = d >> 8;
      r[0x67] = d;
      gfx_start(d);
      return;
    default:
      break;
  }

  s68k_reg_write8(a,     d >> 8);
  s68k_reg_write8(a + 1, d & 0xff);
  return;

write_comm:
  r[a] = d >> 8;
  r[a + 1] = d;
  if (Pico_mcd->m.m68k_poll_cnt)
    SekEndRunS68k(0);
  Pico_mcd->m.m68k_poll_cnt = 0;
}