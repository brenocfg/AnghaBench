#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  m68krcycles_done; int /*<<< orphan*/  state; int /*<<< orphan*/  pc; } ;
typedef  TYPE_1__ SH2 ;

/* Variables and functions */
 int C_M68K_TO_SH2 (TYPE_1__,int) ; 
 scalar_t__ C_SH2_TO_M68K (TYPE_1__,int) ; 
 int /*<<< orphan*/  EL_32X ; 
 int /*<<< orphan*/  EVT_RUN_END ; 
 int /*<<< orphan*/  EVT_RUN_START ; 
 int POPT_EN_DRC ; 
 int PicoOpt ; 
 int /*<<< orphan*/  SH2_STATE_RUN ; 
 int /*<<< orphan*/  elprintf_sh2 (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  pevt_log_sh2_o (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int sh2_execute (TYPE_1__*,int,int) ; 

__attribute__((used)) static inline void run_sh2(SH2 *sh2, int m68k_cycles)
{
  int cycles, done;

  pevt_log_sh2_o(sh2, EVT_RUN_START);
  sh2->state |= SH2_STATE_RUN;
  cycles = C_M68K_TO_SH2(*sh2, m68k_cycles);
  elprintf_sh2(sh2, EL_32X, "+run %u %d @%08x",
    sh2->m68krcycles_done, cycles, sh2->pc);

  done = sh2_execute(sh2, cycles, PicoOpt & POPT_EN_DRC);

  sh2->m68krcycles_done += C_SH2_TO_M68K(*sh2, done);
  sh2->state &= ~SH2_STATE_RUN;
  pevt_log_sh2_o(sh2, EVT_RUN_END);
  elprintf_sh2(sh2, EL_32X, "-run %u %d",
    sh2->m68krcycles_done, done);
}