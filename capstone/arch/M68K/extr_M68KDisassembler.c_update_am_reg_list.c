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
struct TYPE_4__ {int /*<<< orphan*/  base_reg; int /*<<< orphan*/  index_reg; } ;
struct TYPE_5__ {int address_mode; TYPE_1__ mem; int /*<<< orphan*/  reg; } ;
typedef  TYPE_2__ cs_m68k_op ;

/* Variables and functions */
#define  M68K_AM_AREGI_INDEX_8_BIT_DISP 141 
#define  M68K_AM_AREGI_INDEX_BASE_DISP 140 
#define  M68K_AM_MEMI_POST_INDEX 139 
#define  M68K_AM_MEMI_PRE_INDEX 138 
#define  M68K_AM_PCI_INDEX_8_BIT_DISP 137 
#define  M68K_AM_PCI_INDEX_BASE_DISP 136 
#define  M68K_AM_PC_MEMI_POST_INDEX 135 
#define  M68K_AM_PC_MEMI_PRE_INDEX 134 
#define  M68K_AM_REGI_ADDR 133 
#define  M68K_AM_REGI_ADDR_DISP 132 
#define  M68K_AM_REGI_ADDR_POST_INC 131 
#define  M68K_AM_REGI_ADDR_PRE_DEC 130 
#define  M68K_AM_REG_DIRECT_ADDR 129 
#define  M68K_AM_REG_DIRECT_DATA 128 
 int /*<<< orphan*/  add_reg_to_rw_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void update_am_reg_list(m68k_info *info, cs_m68k_op *op, int write)
{
	switch (op->address_mode) {
		case M68K_AM_REG_DIRECT_ADDR:
		case M68K_AM_REG_DIRECT_DATA:
			add_reg_to_rw_list(info, op->reg, write);
			break;

		case M68K_AM_REGI_ADDR_POST_INC:
		case M68K_AM_REGI_ADDR_PRE_DEC:
			add_reg_to_rw_list(info, op->reg, 1);
			break;

		case M68K_AM_REGI_ADDR:
		case M68K_AM_REGI_ADDR_DISP:
			add_reg_to_rw_list(info, op->reg, 0);
			break;

		case M68K_AM_AREGI_INDEX_8_BIT_DISP:
		case M68K_AM_AREGI_INDEX_BASE_DISP:
		case M68K_AM_MEMI_POST_INDEX:
		case M68K_AM_MEMI_PRE_INDEX:
		case M68K_AM_PCI_INDEX_8_BIT_DISP:
		case M68K_AM_PCI_INDEX_BASE_DISP:
		case M68K_AM_PC_MEMI_PRE_INDEX:
		case M68K_AM_PC_MEMI_POST_INDEX:
			add_reg_to_rw_list(info, op->mem.index_reg, 0);
			add_reg_to_rw_list(info, op->mem.base_reg, 0);
			break;

		// no register(s) in the other addressing modes
		default:
			break;
	}
}