#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  ir; } ;
typedef  TYPE_1__ m68k_info ;
struct TYPE_9__ {int /*<<< orphan*/ * operands; } ;
typedef  TYPE_2__ cs_m68k ;

/* Variables and functions */
 int /*<<< orphan*/  M68K_GRP_JUMP ; 
 int /*<<< orphan*/  M68K_INS_JSR ; 
 TYPE_2__* build_init_op (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ea_mode_op (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_insn_group (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void d68000_jsr(m68k_info *info)
{
	cs_m68k* ext = build_init_op(info, M68K_INS_JSR, 1, 0);
	set_insn_group(info, M68K_GRP_JUMP);
	get_ea_mode_op(info, &ext->operands[0], info->ir, 4);
}