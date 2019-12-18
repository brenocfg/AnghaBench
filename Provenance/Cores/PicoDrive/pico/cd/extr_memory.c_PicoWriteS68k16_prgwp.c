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
typedef  int u16 ;
struct TYPE_2__ {int* s68k_regs; scalar_t__ prg_ram; } ;

/* Variables and functions */
 TYPE_1__* Pico_mcd ; 

__attribute__((used)) static void PicoWriteS68k16_prgwp(u32 a, u32 d)
{
  if (a >= (Pico_mcd->s68k_regs[2] << 9))
    *(u16 *)(Pico_mcd->prg_ram + a) = d;
}