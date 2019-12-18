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
typedef  int /*<<< orphan*/  m68k_info ;

/* Variables and functions */
 int /*<<< orphan*/  LIMIT_CPU_TYPES (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M68010_PLUS ; 
 int /*<<< orphan*/  M68K_GRP_RET ; 
 int /*<<< orphan*/  M68K_INS_RTD ; 
 int /*<<< orphan*/  build_absolute_jump_with_immediate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_imm_16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_insn_group (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void d68010_rtd(m68k_info *info)
{
	set_insn_group(info, M68K_GRP_RET);
	LIMIT_CPU_TYPES(info, M68010_PLUS);
	build_absolute_jump_with_immediate(info, M68K_INS_RTD, 0, read_imm_16(info));
}