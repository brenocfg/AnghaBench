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
 int /*<<< orphan*/  LIMIT_CPU_TYPES (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M68020_PLUS ; 
 int /*<<< orphan*/  M68K_INS_FRESTORE ; 
 TYPE_2__* build_init_op (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ea_mode_op (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void d68020_cprestore(m68k_info *info)
{
	cs_m68k* ext;
	LIMIT_CPU_TYPES(info, M68020_PLUS);

	ext = build_init_op(info, M68K_INS_FRESTORE, 1, 0);
	get_ea_mode_op(info, &ext->operands[0], info->ir, 1);
}