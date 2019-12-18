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
 int CM_compareRun (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CycloneRun (TYPE_1__*) ; 
 TYPE_1__ PicoCpuCM68k ; 
 int SekCycleAim ; 
 int SekCycleCnt ; 
 int fm68k_emulate (int,int /*<<< orphan*/ ) ; 
 int m68k_execute (int) ; 

void SekStepM68k(void)
{
  SekCycleAim=SekCycleCnt+1;
#if defined(EMU_CORE_DEBUG)
  SekCycleCnt+=CM_compareRun(1, 0);
#elif defined(EMU_C68K)
  PicoCpuCM68k.cycles=1;
  CycloneRun(&PicoCpuCM68k);
  SekCycleCnt+=1-PicoCpuCM68k.cycles;
#elif defined(EMU_M68K)
  SekCycleCnt+=m68k_execute(1);
#elif defined(EMU_F68K)
  SekCycleCnt+=fm68k_emulate(1, 0);
#endif
}