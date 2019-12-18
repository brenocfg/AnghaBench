#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int CPU_C_FLAG ; 
 int CPU_N_FLAG ; 
 int CPU_V_FLAG ; 
 int CPU_Z_FLAG ; 
 int /*<<< orphan*/  CPU_regA ; 
 int CPU_regP ; 
 int /*<<< orphan*/  CPU_regPC ; 
 int /*<<< orphan*/  CPU_regS ; 
 int /*<<< orphan*/  CPU_regX ; 
 int /*<<< orphan*/  CPU_regY ; 
 int /*<<< orphan*/  MONITOR_ShowState (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,char,char,char) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void show_state(void)
{
	MONITOR_ShowState(stdout, CPU_regPC, CPU_regA, CPU_regX, CPU_regY, CPU_regS,
		(char) ((CPU_regP & CPU_N_FLAG) ? 'N' : '-'), (char) ((CPU_regP & CPU_V_FLAG) ? 'V' : '-'),
		(char) ((CPU_regP & CPU_Z_FLAG) ? 'Z' : '-'), (char) ((CPU_regP & CPU_C_FLAG) ? 'C' : '-'));
}