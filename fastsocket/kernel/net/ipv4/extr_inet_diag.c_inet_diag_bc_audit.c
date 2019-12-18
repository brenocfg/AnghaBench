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
struct inet_diag_bc_op {int code; int no; int yes; } ;

/* Variables and functions */
 int EINVAL ; 
#define  INET_DIAG_BC_AUTO 136 
#define  INET_DIAG_BC_D_COND 135 
#define  INET_DIAG_BC_D_GE 134 
#define  INET_DIAG_BC_D_LE 133 
#define  INET_DIAG_BC_JMP 132 
#define  INET_DIAG_BC_NOP 131 
#define  INET_DIAG_BC_S_COND 130 
#define  INET_DIAG_BC_S_GE 129 
#define  INET_DIAG_BC_S_LE 128 
 int /*<<< orphan*/  valid_cc (void const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int inet_diag_bc_audit(const void *bytecode, int bytecode_len)
{
	const void *bc = bytecode;
	int  len = bytecode_len;

	while (len > 0) {
		const struct inet_diag_bc_op *op = bc;

//printk("BC: %d %d %d {%d} / %d\n", op->code, op->yes, op->no, op[1].no, len);
		switch (op->code) {
		case INET_DIAG_BC_AUTO:
		case INET_DIAG_BC_S_COND:
		case INET_DIAG_BC_D_COND:
		case INET_DIAG_BC_S_GE:
		case INET_DIAG_BC_S_LE:
		case INET_DIAG_BC_D_GE:
		case INET_DIAG_BC_D_LE:
		case INET_DIAG_BC_JMP:
			if (op->no < 4 || op->no > len + 4 || op->no & 3)
				return -EINVAL;
			if (op->no < len &&
			    !valid_cc(bytecode, bytecode_len, len - op->no))
				return -EINVAL;
			break;
		case INET_DIAG_BC_NOP:
			break;
		default:
			return -EINVAL;
		}
		if (op->yes < 4 || op->yes > len + 4 || op->yes & 3)
			return -EINVAL;
		bc  += op->yes;
		len -= op->yes;
	}
	return len == 0 ? 0 : -EINVAL;
}