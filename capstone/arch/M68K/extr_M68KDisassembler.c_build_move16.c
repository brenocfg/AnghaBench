#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  m68k_info ;
struct TYPE_4__ {int address_mode; int imm; scalar_t__ reg; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ cs_m68k_op ;
struct TYPE_5__ {TYPE_1__* operands; } ;
typedef  TYPE_2__ cs_m68k ;

/* Variables and functions */
 int const M68K_AM_REGI_ADDR_POST_INC ; 
 int const M68K_AM_REG_DIRECT_ADDR ; 
 int /*<<< orphan*/  M68K_INS_MOVE16 ; 
 int /*<<< orphan*/  M68K_OP_MEM ; 
 scalar_t__ M68K_REG_A0 ; 
 TYPE_2__* build_init_op (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void build_move16(m68k_info *info, int data[2], int modes[2])
{
	cs_m68k* ext = build_init_op(info, M68K_INS_MOVE16, 2, 0);
	int i;

	for (i = 0; i < 2; ++i) {
		cs_m68k_op* op = &ext->operands[i];
		const int d = data[i];
		const int m = modes[i];

		op->type = M68K_OP_MEM;

		if (m == M68K_AM_REGI_ADDR_POST_INC || m == M68K_AM_REG_DIRECT_ADDR) {
			op->address_mode = m;
			op->reg = M68K_REG_A0 + d;
		} else {
			op->address_mode = m;
			op->imm = d;
		}
	}
}