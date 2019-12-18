#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  ir; TYPE_1__* inst; } ;
typedef  TYPE_2__ m68k_info ;
struct TYPE_12__ {int /*<<< orphan*/ * operands; } ;
typedef  TYPE_3__ cs_m68k ;
struct TYPE_10__ {int Opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIMIT_CPU_TYPES (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M68020_PLUS ; 
 int /*<<< orphan*/  M68K_INS_FSF ; 
 TYPE_3__* build_init_op (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  get_ea_mode_op (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int read_imm_16 (TYPE_2__*) ; 

__attribute__((used)) static void d68020_cpscc(m68k_info *info)
{
	cs_m68k* ext;

	LIMIT_CPU_TYPES(info, M68020_PLUS);
	ext = build_init_op(info, M68K_INS_FSF, 1, 1);

	// these are all in row with the extension so just doing a add here is fine
	info->inst->Opcode += (read_imm_16(info) & 0x2f);

	get_ea_mode_op(info, &ext->operands[0], info->ir, 1);
}