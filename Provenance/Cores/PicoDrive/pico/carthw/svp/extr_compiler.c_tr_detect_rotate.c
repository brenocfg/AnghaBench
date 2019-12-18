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

/* Variables and functions */
 int /*<<< orphan*/  EOP_MOV_REG_LSL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EOP_ORR_REG_LSR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int PROGRAM (int) ; 
 int n_in_ops ; 
 int /*<<< orphan*/  tr_bank_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tr_bank_write (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tr_detect_rotate(unsigned int op, int *pc, int imm)
{
	// @ 3DA2 and 426A
	// ld PMC, (r3|00)
	// ld (r3|00), PMC
	// ld -, AL
	if (op != 0x02e3 || PROGRAM(*pc) != 0x04e3 || PROGRAM(*pc + 1) != 0x000f) return 0;

	tr_bank_read(0);
	EOP_MOV_REG_LSL(0, 0, 4);
	EOP_ORR_REG_LSR(0, 0, 0, 16);
	tr_bank_write(0);
	(*pc) += 2;
	n_in_ops += 2;
	return 3;
}