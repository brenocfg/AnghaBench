#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct prefix_bits {int dummy; } ;
typedef  enum reason_type { ____Placeholder_reason_type } reason_type ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_OP_TYPE (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMM_WRITE ; 
 int OTHERS ; 
 int /*<<< orphan*/  REG_READ ; 
 int /*<<< orphan*/  REG_WRITE ; 
 int /*<<< orphan*/  get_opcode (unsigned char*,unsigned int*) ; 
 int /*<<< orphan*/  imm_wop ; 
 int /*<<< orphan*/  reg_rop ; 
 int /*<<< orphan*/  reg_wop ; 
 int /*<<< orphan*/  skip_prefix (unsigned char*,struct prefix_bits*) ; 

enum reason_type get_ins_type(unsigned long ins_addr)
{
	unsigned int opcode;
	unsigned char *p;
	struct prefix_bits prf;
	int i;
	enum reason_type rv = OTHERS;

	p = (unsigned char *)ins_addr;
	p += skip_prefix(p, &prf);
	p += get_opcode(p, &opcode);

	CHECK_OP_TYPE(opcode, reg_rop, REG_READ);
	CHECK_OP_TYPE(opcode, reg_wop, REG_WRITE);
	CHECK_OP_TYPE(opcode, imm_wop, IMM_WRITE);

exit:
	return rv;
}