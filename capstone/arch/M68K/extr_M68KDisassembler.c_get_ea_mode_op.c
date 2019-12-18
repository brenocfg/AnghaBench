#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
typedef  int /*<<< orphan*/  m68k_info ;
typedef  void* int16_t ;
struct TYPE_5__ {int base_reg; void* disp; } ;
struct TYPE_6__ {int reg; int imm; void* type; int /*<<< orphan*/  address_mode; TYPE_1__ mem; } ;
typedef  TYPE_2__ cs_m68k_op ;

/* Variables and functions */
 int /*<<< orphan*/  M68K_AM_ABSOLUTE_DATA_LONG ; 
 int /*<<< orphan*/  M68K_AM_ABSOLUTE_DATA_SHORT ; 
 int /*<<< orphan*/  M68K_AM_IMMEDIATE ; 
 int /*<<< orphan*/  M68K_AM_PCI_DISP ; 
 int /*<<< orphan*/  M68K_AM_REGI_ADDR ; 
 int /*<<< orphan*/  M68K_AM_REGI_ADDR_DISP ; 
 int /*<<< orphan*/  M68K_AM_REGI_ADDR_POST_INC ; 
 int /*<<< orphan*/  M68K_AM_REGI_ADDR_PRE_DEC ; 
 int /*<<< orphan*/  M68K_AM_REG_DIRECT_ADDR ; 
 int /*<<< orphan*/  M68K_AM_REG_DIRECT_DATA ; 
 void* M68K_OP_IMM ; 
 void* M68K_OP_MEM ; 
 void* M68K_OP_REG ; 
 int M68K_REG_A0 ; 
 int M68K_REG_D0 ; 
 int /*<<< orphan*/  get_with_index_address_mode (int /*<<< orphan*/ *,TYPE_2__*,int,int,int) ; 
 int read_imm_16 (int /*<<< orphan*/ *) ; 
 void* read_imm_32 (int /*<<< orphan*/ *) ; 
 int read_imm_64 (int /*<<< orphan*/ *) ; 
 int read_imm_8 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void get_ea_mode_op(m68k_info *info, cs_m68k_op* op, uint instruction, uint size)
{
	// default to memory

	op->type = M68K_OP_MEM;

	switch (instruction & 0x3f) {
		case 0x00: case 0x01: case 0x02: case 0x03: case 0x04: case 0x05: case 0x06: case 0x07:
			/* data register direct */
			op->address_mode = M68K_AM_REG_DIRECT_DATA;
			op->reg = M68K_REG_D0 + (instruction & 7);
			op->type = M68K_OP_REG;
			break;

		case 0x08: case 0x09: case 0x0a: case 0x0b: case 0x0c: case 0x0d: case 0x0e: case 0x0f:
			/* address register direct */
			op->address_mode = M68K_AM_REG_DIRECT_ADDR;
			op->reg = M68K_REG_A0 + (instruction & 7);
			op->type = M68K_OP_REG;
			break;

		case 0x10: case 0x11: case 0x12: case 0x13: case 0x14: case 0x15: case 0x16: case 0x17:
			/* address register indirect */
			op->address_mode = M68K_AM_REGI_ADDR;
			op->reg = M68K_REG_A0 + (instruction & 7);
			break;

		case 0x18: case 0x19: case 0x1a: case 0x1b: case 0x1c: case 0x1d: case 0x1e: case 0x1f:
			/* address register indirect with postincrement */
			op->address_mode = M68K_AM_REGI_ADDR_POST_INC;
			op->reg = M68K_REG_A0 + (instruction & 7);
			break;

		case 0x20: case 0x21: case 0x22: case 0x23: case 0x24: case 0x25: case 0x26: case 0x27:
			/* address register indirect with predecrement */
			op->address_mode = M68K_AM_REGI_ADDR_PRE_DEC;
			op->reg = M68K_REG_A0 + (instruction & 7);
			break;

		case 0x28: case 0x29: case 0x2a: case 0x2b: case 0x2c: case 0x2d: case 0x2e: case 0x2f:
			/* address register indirect with displacement*/
			op->address_mode = M68K_AM_REGI_ADDR_DISP;
			op->mem.base_reg = M68K_REG_A0 + (instruction & 7);
			op->mem.disp = (int16_t)read_imm_16(info);
			break;

		case 0x30: case 0x31: case 0x32: case 0x33: case 0x34: case 0x35: case 0x36: case 0x37:
			/* address register indirect with index */
			get_with_index_address_mode(info, op, instruction, size, false);
			break;

		case 0x38:
			/* absolute short address */
			op->address_mode = M68K_AM_ABSOLUTE_DATA_SHORT;
			op->imm = read_imm_16(info);
			break;

		case 0x39:
			/* absolute long address */
			op->address_mode = M68K_AM_ABSOLUTE_DATA_LONG;
			op->imm = read_imm_32(info);
			break;

		case 0x3a:
			/* program counter with displacement */
			op->address_mode = M68K_AM_PCI_DISP;
			op->mem.disp = (int16_t)read_imm_16(info);
			break;

		case 0x3b:
			/* program counter with index */
			get_with_index_address_mode(info, op, instruction, size, true);
			break;

		case 0x3c:
			op->address_mode = M68K_AM_IMMEDIATE;
			op->type = M68K_OP_IMM;

			if (size == 1)
				op->imm = read_imm_8(info) & 0xff;
			else if (size == 2)
				op->imm = read_imm_16(info) & 0xffff;
			else if (size == 4)
				op->imm = read_imm_32(info);
			else
				op->imm = read_imm_64(info);

			break;

		default:
			break;
	}
}