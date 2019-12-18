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
 scalar_t__ BIT_3 (int) ; 
 int /*<<< orphan*/  DASMFLAG_STEP_OUT ; 
 int /*<<< orphan*/  LIMIT_CPU_TYPES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M68020_ONLY ; 
 int /*<<< orphan*/  SET_OPCODE_FLAGS (int /*<<< orphan*/ ) ; 
 int g_cpu_ir ; 
 int /*<<< orphan*/  g_dasm_str ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char,int) ; 

__attribute__((used)) static void d68020_rtm(void)
{
	LIMIT_CPU_TYPES(M68020_ONLY);
	sprintf(g_dasm_str, "rtm     %c%d; (2+)", BIT_3(g_cpu_ir) ? 'A' : 'D', g_cpu_ir&7);
	SET_OPCODE_FLAGS(DASMFLAG_STEP_OUT);
}