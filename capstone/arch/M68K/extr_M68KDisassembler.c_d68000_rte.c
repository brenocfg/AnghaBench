#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  inst; } ;
typedef  TYPE_1__ m68k_info ;

/* Variables and functions */
 int /*<<< orphan*/  M68K_GRP_IRET ; 
 int /*<<< orphan*/  M68K_INS_RTE ; 
 int /*<<< orphan*/  MCInst_setOpcode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_insn_group (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void d68000_rte(m68k_info *info)
{
	set_insn_group(info, M68K_GRP_IRET);
	MCInst_setOpcode(info->inst, M68K_INS_RTE);
}