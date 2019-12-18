#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_5__ {scalar_t__ peri_regs; } ;
typedef  TYPE_1__ SH2 ;

/* Variables and functions */
 int /*<<< orphan*/  EL_32XP ; 
 int /*<<< orphan*/  elprintf_sh2 (TYPE_1__*,int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh2_pc (TYPE_1__*) ; 

u32 sh2_peripheral_read16(u32 a, SH2 *sh2)
{
  u16 *r = (void *)sh2->peri_regs;
  u32 d;

  a &= 0x1ff;
  d = r[(a / 2) ^ 1];

  elprintf_sh2(sh2, EL_32XP, "peri r16 [%08x]     %04x @%06x",
    a | ~0x1ff, d, sh2_pc(sh2));
  return d;
}