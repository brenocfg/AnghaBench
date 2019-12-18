#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * operands; } ;
struct TYPE_6__ {TYPE_2__ extension; } ;
typedef  TYPE_1__ m68k_info ;
typedef  int /*<<< orphan*/  cs_m68k_op ;
typedef  TYPE_2__ cs_m68k ;

/* Variables and functions */
 int /*<<< orphan*/  LIMIT_CPU_TYPES (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M68020_PLUS ; 
 int /*<<< orphan*/  M68K_INS_BFINS ; 
 int /*<<< orphan*/  build_bitfield_ins (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void d68020_bfins(m68k_info *info)
{
	cs_m68k* ext = &info->extension;
	cs_m68k_op temp;

	LIMIT_CPU_TYPES(info, M68020_PLUS);
	build_bitfield_ins(info, M68K_INS_BFINS, true);

	// a bit hacky but we need to flip the args on only this instruction

	temp = ext->operands[0];
	ext->operands[0] = ext->operands[1];
	ext->operands[1] = temp;
}