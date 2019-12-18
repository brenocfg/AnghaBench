#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_6__ {int cpu_size; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {TYPE_1__ op_size; scalar_t__ op_count; } ;
struct TYPE_7__ {TYPE_3__ extension; int /*<<< orphan*/  inst; } ;
typedef  TYPE_2__ m68k_info ;
typedef  TYPE_3__ cs_m68k ;

/* Variables and functions */
 int /*<<< orphan*/  M68K_SIZE_TYPE_CPU ; 
 int /*<<< orphan*/  MCInst_setOpcode (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static cs_m68k* build_init_op(m68k_info *info, int opcode, int count, int size)
{
	cs_m68k* ext;

	MCInst_setOpcode(info->inst, opcode);

	ext = &info->extension;

	ext->op_count = (uint8_t)count;
	ext->op_size.type = M68K_SIZE_TYPE_CPU;
	ext->op_size.cpu_size = size;

	return ext;
}