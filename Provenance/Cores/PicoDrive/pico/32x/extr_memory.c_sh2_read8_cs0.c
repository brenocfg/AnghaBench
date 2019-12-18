#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_15__ {scalar_t__ is_slave; } ;
struct TYPE_14__ {int* b; } ;
struct TYPE_13__ {int* b; } ;
struct TYPE_12__ {int* pal; TYPE_2__ sh2_rom_s; TYPE_1__ sh2_rom_m; } ;
typedef  TYPE_3__ SH2 ;

/* Variables and functions */
 int /*<<< orphan*/  EL_32X ; 
 TYPE_11__* Pico32xMem ; 
 int /*<<< orphan*/  SH2_STATE_VPOLL ; 
 int /*<<< orphan*/  elprintf_sh2 (TYPE_3__*,int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ) ; 
 int p32x_sh2reg_read16 (int,TYPE_3__*) ; 
 int p32x_vdp_read16 (int) ; 
 int /*<<< orphan*/  sh2_burn_cycles (TYPE_3__*,int) ; 
 int /*<<< orphan*/  sh2_pc (TYPE_3__*) ; 
 int /*<<< orphan*/  sh2_poll_detect (TYPE_3__*,int,int /*<<< orphan*/ ,int) ; 
 int sh2_read8_unmapped (int,TYPE_3__*) ; 

__attribute__((used)) static u32 sh2_read8_cs0(u32 a, SH2 *sh2)
{
  u32 d = 0;

  sh2_burn_cycles(sh2, 1*2);

  // 0x3ffc0 is veridied
  if ((a & 0x3ffc0) == 0x4000) {
    d = p32x_sh2reg_read16(a, sh2);
    goto out_16to8;
  }

  if ((a & 0x3fff0) == 0x4100) {
    d = p32x_vdp_read16(a);
    sh2_poll_detect(sh2, a, SH2_STATE_VPOLL, 7);
    goto out_16to8;
  }

  // TODO: mirroring?
  if (!sh2->is_slave && a < sizeof(Pico32xMem->sh2_rom_m))
    return Pico32xMem->sh2_rom_m.b[a ^ 1];
  if (sh2->is_slave  && a < sizeof(Pico32xMem->sh2_rom_s))
    return Pico32xMem->sh2_rom_s.b[a ^ 1];

  if ((a & 0x3fe00) == 0x4200) {
    d = Pico32xMem->pal[(a & 0x1ff) / 2];
    goto out_16to8;
  }

  return sh2_read8_unmapped(a, sh2);

out_16to8:
  if (a & 1)
    d &= 0xff;
  else
    d >>= 8;

  elprintf_sh2(sh2, EL_32X, "r8  [%08x]       %02x @%06x",
    a, d, sh2_pc(sh2));
  return d;
}