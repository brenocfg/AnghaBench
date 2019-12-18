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
struct TYPE_4__ {int /*<<< orphan*/ * rom; } ;
struct TYPE_3__ {scalar_t__* sp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CycloneReset (int /*<<< orphan*/ *) ; 
 TYPE_2__ Pico ; 
 int /*<<< orphan*/  PicoCpuCM68k ; 
 int /*<<< orphan*/  PicoCpuFM68k ; 
 int /*<<< orphan*/  PicoCpuMM68k ; 
 scalar_t__ REG_USP ; 
 int /*<<< orphan*/  fm68k_reset () ; 
 int /*<<< orphan*/ * g_m68kcontext ; 
 int /*<<< orphan*/  m68k_pulse_reset () ; 
 int /*<<< orphan*/  m68k_set_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m68k_set_irq (int /*<<< orphan*/ ) ; 
 TYPE_1__ m68ki_cpu ; 

int SekReset(void)
{
  if (Pico.rom==NULL) return 1;

#ifdef EMU_C68K
  CycloneReset(&PicoCpuCM68k);
#endif
#ifdef EMU_M68K
  m68k_set_context(&PicoCpuMM68k); // if we ever reset m68k, we always need it's context to be set
  m68ki_cpu.sp[0]=0;
  m68k_set_irq(0);
  m68k_pulse_reset();
  REG_USP = 0; // ?
#endif
#ifdef EMU_F68K
  {
    g_m68kcontext = &PicoCpuFM68k;
    fm68k_reset();
  }
#endif

  return 0;
}