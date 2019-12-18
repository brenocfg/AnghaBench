#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int cycles; } ;
struct TYPE_5__ {scalar_t__ s68k_poll_a; } ;
struct TYPE_6__ {TYPE_1__ m; } ;

/* Variables and functions */
 int /*<<< orphan*/  CycloneRun (TYPE_3__*) ; 
 TYPE_3__ PicoCpuCS68k ; 
 int /*<<< orphan*/  PicoCpuFM68k ; 
 int /*<<< orphan*/  PicoCpuFS68k ; 
 int /*<<< orphan*/  PicoCpuMM68k ; 
 int /*<<< orphan*/  PicoCpuMS68k ; 
 TYPE_2__* Pico_mcd ; 
 int SekCycleAimS68k ; 
 int SekCycleCntS68k ; 
 scalar_t__ SekShouldInterrupt () ; 
 int fm68k_emulate (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_m68kcontext ; 
 int m68k_execute (int) ; 
 int /*<<< orphan*/  m68k_set_context (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void SekRunS68k(unsigned int to)
{
  int cyc_do;

  SekCycleAimS68k = to;
  if ((cyc_do = SekCycleAimS68k - SekCycleCntS68k) <= 0)
    return;

  if (SekShouldInterrupt())
    Pico_mcd->m.s68k_poll_a = 0;

  SekCycleCntS68k += cyc_do;
#if defined(EMU_C68K)
  PicoCpuCS68k.cycles = cyc_do;
  CycloneRun(&PicoCpuCS68k);
  SekCycleCntS68k -= PicoCpuCS68k.cycles;
#elif defined(EMU_M68K)
  m68k_set_context(&PicoCpuMS68k);
  SekCycleCntS68k += m68k_execute(cyc_do) - cyc_do;
  m68k_set_context(&PicoCpuMM68k);
#elif defined(EMU_F68K)
  g_m68kcontext = &PicoCpuFS68k;
  SekCycleCntS68k += fm68k_emulate(cyc_do, 0) - cyc_do;
  g_m68kcontext = &PicoCpuFM68k;
#endif
}