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
struct pt_regs {unsigned long r0; unsigned long r1; unsigned long r2; unsigned long r3; unsigned long r4; unsigned long r5; unsigned long r6; unsigned long r7; unsigned long p0; unsigned long p1; unsigned long p2; unsigned long p3; unsigned long p4; unsigned long p5; unsigned long fp; unsigned long i0; unsigned long i1; unsigned long i2; unsigned long i3; unsigned long m0; unsigned long m1; unsigned long m2; unsigned long m3; unsigned long b0; unsigned long b1; unsigned long b2; unsigned long b3; unsigned long l0; unsigned long l1; unsigned long l2; unsigned long l3; unsigned long a0x; unsigned long a0w; unsigned long a1x; unsigned long a1w; unsigned long rets; unsigned long lc0; unsigned long lt0; unsigned long lb0; unsigned long lc1; unsigned long lt1; unsigned long lb1; unsigned long usp; unsigned long syscfg; unsigned long retx; unsigned long retn; unsigned long rete; unsigned long pc; unsigned long astat; unsigned long seqstat; unsigned long ipend; } ;

/* Variables and functions */
 size_t BFIN_A0_DOT_W ; 
 size_t BFIN_A0_DOT_X ; 
 size_t BFIN_A1_DOT_W ; 
 size_t BFIN_A1_DOT_X ; 
 size_t BFIN_ASTAT ; 
 size_t BFIN_B0 ; 
 size_t BFIN_B1 ; 
 size_t BFIN_B2 ; 
 size_t BFIN_B3 ; 
 size_t BFIN_FP ; 
 size_t BFIN_I0 ; 
 size_t BFIN_I1 ; 
 size_t BFIN_I2 ; 
 size_t BFIN_I3 ; 
 size_t BFIN_IPEND ; 
 size_t BFIN_L0 ; 
 size_t BFIN_L1 ; 
 size_t BFIN_L2 ; 
 size_t BFIN_L3 ; 
 size_t BFIN_LB0 ; 
 size_t BFIN_LB1 ; 
 size_t BFIN_LC0 ; 
 size_t BFIN_LC1 ; 
 size_t BFIN_LT0 ; 
 size_t BFIN_LT1 ; 
 size_t BFIN_M0 ; 
 size_t BFIN_M1 ; 
 size_t BFIN_M2 ; 
 size_t BFIN_M3 ; 
 size_t BFIN_P0 ; 
 size_t BFIN_P1 ; 
 size_t BFIN_P2 ; 
 size_t BFIN_P3 ; 
 size_t BFIN_P4 ; 
 size_t BFIN_P5 ; 
 size_t BFIN_PC ; 
 size_t BFIN_R0 ; 
 size_t BFIN_R1 ; 
 size_t BFIN_R2 ; 
 size_t BFIN_R3 ; 
 size_t BFIN_R4 ; 
 size_t BFIN_R5 ; 
 size_t BFIN_R6 ; 
 size_t BFIN_R7 ; 
 size_t BFIN_RETE ; 
 size_t BFIN_RETN ; 
 size_t BFIN_RETS ; 
 size_t BFIN_SEQSTAT ; 
 size_t BFIN_SYSCFG ; 
 size_t BFIN_USP ; 

void gdb_regs_to_pt_regs(unsigned long *gdb_regs, struct pt_regs *regs)
{
	regs->r0 = gdb_regs[BFIN_R0];
	regs->r1 = gdb_regs[BFIN_R1];
	regs->r2 = gdb_regs[BFIN_R2];
	regs->r3 = gdb_regs[BFIN_R3];
	regs->r4 = gdb_regs[BFIN_R4];
	regs->r5 = gdb_regs[BFIN_R5];
	regs->r6 = gdb_regs[BFIN_R6];
	regs->r7 = gdb_regs[BFIN_R7];
	regs->p0 = gdb_regs[BFIN_P0];
	regs->p1 = gdb_regs[BFIN_P1];
	regs->p2 = gdb_regs[BFIN_P2];
	regs->p3 = gdb_regs[BFIN_P3];
	regs->p4 = gdb_regs[BFIN_P4];
	regs->p5 = gdb_regs[BFIN_P5];
	regs->fp = gdb_regs[BFIN_FP];
	regs->i0 = gdb_regs[BFIN_I0];
	regs->i1 = gdb_regs[BFIN_I1];
	regs->i2 = gdb_regs[BFIN_I2];
	regs->i3 = gdb_regs[BFIN_I3];
	regs->m0 = gdb_regs[BFIN_M0];
	regs->m1 = gdb_regs[BFIN_M1];
	regs->m2 = gdb_regs[BFIN_M2];
	regs->m3 = gdb_regs[BFIN_M3];
	regs->b0 = gdb_regs[BFIN_B0];
	regs->b1 = gdb_regs[BFIN_B1];
	regs->b2 = gdb_regs[BFIN_B2];
	regs->b3 = gdb_regs[BFIN_B3];
	regs->l0 = gdb_regs[BFIN_L0];
	regs->l1 = gdb_regs[BFIN_L1];
	regs->l2 = gdb_regs[BFIN_L2];
	regs->l3 = gdb_regs[BFIN_L3];
	regs->a0x = gdb_regs[BFIN_A0_DOT_X];
	regs->a0w = gdb_regs[BFIN_A0_DOT_W];
	regs->a1x = gdb_regs[BFIN_A1_DOT_X];
	regs->a1w = gdb_regs[BFIN_A1_DOT_W];
	regs->rets = gdb_regs[BFIN_RETS];
	regs->lc0 = gdb_regs[BFIN_LC0];
	regs->lt0 = gdb_regs[BFIN_LT0];
	regs->lb0 = gdb_regs[BFIN_LB0];
	regs->lc1 = gdb_regs[BFIN_LC1];
	regs->lt1 = gdb_regs[BFIN_LT1];
	regs->lb1 = gdb_regs[BFIN_LB1];
	regs->usp = gdb_regs[BFIN_USP];
	regs->syscfg = gdb_regs[BFIN_SYSCFG];
	regs->retx = gdb_regs[BFIN_PC];
	regs->retn = gdb_regs[BFIN_RETN];
	regs->rete = gdb_regs[BFIN_RETE];
	regs->pc = gdb_regs[BFIN_PC];

#if 0				/* can't change these */
	regs->astat = gdb_regs[BFIN_ASTAT];
	regs->seqstat = gdb_regs[BFIN_SEQSTAT];
	regs->ipend = gdb_regs[BFIN_IPEND];
#endif
}