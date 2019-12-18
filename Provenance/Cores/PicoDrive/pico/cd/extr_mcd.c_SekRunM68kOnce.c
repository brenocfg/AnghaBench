#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int cycles; } ;

/* Variables and functions */
 int /*<<< orphan*/  CycloneRun (TYPE_1__*) ; 
 int /*<<< orphan*/  EVT_RUN_END ; 
 int /*<<< orphan*/  EVT_RUN_START ; 
 TYPE_1__ PicoCpuCM68k ; 
 int SekCycleAim ; 
 int SekCycleCnt ; 
 scalar_t__ SekCyclesLeft ; 
 int /*<<< orphan*/  SekTrace (int /*<<< orphan*/ ) ; 
 int fm68k_emulate (int,int /*<<< orphan*/ ) ; 
 int m68k_execute (int) ; 
 int /*<<< orphan*/  pevt_log_m68k_o (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void SekRunM68kOnce(void)
{
  int cyc_do;
  pevt_log_m68k_o(EVT_RUN_START);

  if ((cyc_do = SekCycleAim - SekCycleCnt) > 0) {
    SekCycleCnt += cyc_do;

#if defined(EMU_C68K)
    PicoCpuCM68k.cycles = cyc_do;
    CycloneRun(&PicoCpuCM68k);
    SekCycleCnt -= PicoCpuCM68k.cycles;
#elif defined(EMU_M68K)
    SekCycleCnt += m68k_execute(cyc_do) - cyc_do;
#elif defined(EMU_F68K)
    SekCycleCnt += fm68k_emulate(cyc_do, 0) - cyc_do;
#endif
  }

  SekCyclesLeft = 0;

  SekTrace(0);
  pevt_log_m68k_o(EVT_RUN_END);
}