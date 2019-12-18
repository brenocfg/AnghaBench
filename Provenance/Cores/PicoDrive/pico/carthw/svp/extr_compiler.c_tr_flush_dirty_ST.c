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
 int /*<<< orphan*/  EOP_BIC_IMM (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EOP_MRS (int) ; 
 int /*<<< orphan*/  EOP_ORR_REG_LSR (int,int,int,int) ; 
 int KRREG_ST ; 
 int dirty_regb ; 
 int* hostreg_r ; 

__attribute__((used)) static void tr_flush_dirty_ST(void)
{
	if (!(dirty_regb & KRREG_ST)) return;
	EOP_BIC_IMM(6,6,0,0x0f);
	EOP_MRS(1);
	EOP_ORR_REG_LSR(6,6,1,28);
	dirty_regb &= ~KRREG_ST;
	hostreg_r[1] = -1;
}