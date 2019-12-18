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
 int /*<<< orphan*/  EOP_ADD_IMM (int,int,int,int) ; 
 int /*<<< orphan*/  EOP_LDRH_IMM (int /*<<< orphan*/ ,int,int) ; 
 int* hostreg_r ; 

__attribute__((used)) static void tr_bank_read(int addr) /* word addr 0-0x1ff */
{
	int breg = 7;
	if (addr > 0x7f) {
		if (hostreg_r[1] != (0x100000|((addr&0x180)<<1))) {
			EOP_ADD_IMM(1,7,30/2,(addr&0x180)>>1);	// add  r1, r7, ((op&0x180)<<1)
			hostreg_r[1] = 0x100000|((addr&0x180)<<1);
		}
		breg = 1;
	}
	EOP_LDRH_IMM(0,breg,(addr&0x7f)<<1);	// ldrh r0, [r1, (op&0x7f)<<1]
	hostreg_r[0] = -1;
}