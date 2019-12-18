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
typedef  int u32 ;

/* Variables and functions */
#define  A_OP_ADD 133 
#define  A_OP_BIC 132 
#define  A_OP_EOR 131 
#define  A_OP_MOV 130 
 int A_OP_MVN ; 
#define  A_OP_ORR 129 
#define  A_OP_SUB 128 
 int /*<<< orphan*/  EOP_C_DOP_IMM (int,int,int,int,int,int,int) ; 

__attribute__((used)) static void emith_op_imm2(int cond, int s, int op, int rd, int rn, unsigned int imm)
{
	int ror2;
	u32 v;

	switch (op) {
	case A_OP_MOV:
		rn = 0;
		if (~imm < 0x10000) {
			imm = ~imm;
			op = A_OP_MVN;
		}
		break;

	case A_OP_EOR:
	case A_OP_SUB:
	case A_OP_ADD:
	case A_OP_ORR:
	case A_OP_BIC:
		if (s == 0 && imm == 0)
			return;
		break;
	}

	for (v = imm, ror2 = 0; ; ror2 -= 8/2) {
		/* shift down to get 'best' rot2 */
		for (; v && !(v & 3); v >>= 2)
			ror2--;

		EOP_C_DOP_IMM(cond, op, s, rn, rd, ror2 & 0x0f, v & 0xff);

		v >>= 8;
		if (v == 0)
			break;
		if (op == A_OP_MOV)
			op = A_OP_ORR;
		if (op == A_OP_MVN)
			op = A_OP_BIC;
		rn = rd;
	}
}