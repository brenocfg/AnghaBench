#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
struct TYPE_8__ {TYPE_1__* inst; } ;
typedef  TYPE_2__ m68k_info ;
struct TYPE_7__ {int Opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIMIT_CPU_TYPES (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M68020_PLUS ; 
 int /*<<< orphan*/  M68K_INS_FTRAPF ; 
 int /*<<< orphan*/  build_init_op (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read_imm_16 (TYPE_2__*) ; 

__attribute__((used)) static void d68020_cptrapcc_0(m68k_info *info)
{
	uint extension1;
	LIMIT_CPU_TYPES(info, M68020_PLUS);

	extension1 = read_imm_16(info);

	build_init_op(info, M68K_INS_FTRAPF, 0, 0);

	// these are all in row with the extension so just doing a add here is fine
	info->inst->Opcode += (extension1 & 0x2f);
}