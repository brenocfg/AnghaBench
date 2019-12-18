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
typedef  int /*<<< orphan*/  u64 ;
struct pt_regs {int /*<<< orphan*/  r31; int /*<<< orphan*/  r30; int /*<<< orphan*/  r29; int /*<<< orphan*/  r28; int /*<<< orphan*/  r27; int /*<<< orphan*/  r26; int /*<<< orphan*/  r25; int /*<<< orphan*/  r24; int /*<<< orphan*/  r23; int /*<<< orphan*/  r22; int /*<<< orphan*/  r21; int /*<<< orphan*/  r20; int /*<<< orphan*/  r19; int /*<<< orphan*/  r18; int /*<<< orphan*/  r17; int /*<<< orphan*/  r16; int /*<<< orphan*/  r15; int /*<<< orphan*/  r14; int /*<<< orphan*/  r13; int /*<<< orphan*/  r12; int /*<<< orphan*/  r11; int /*<<< orphan*/  r10; int /*<<< orphan*/  r9; int /*<<< orphan*/  r8; int /*<<< orphan*/  r3; int /*<<< orphan*/  r2; int /*<<< orphan*/  r1; int /*<<< orphan*/  ar_rsc; int /*<<< orphan*/  b0; int /*<<< orphan*/  pr; int /*<<< orphan*/  cr_ifs; int /*<<< orphan*/  cr_ipsr; int /*<<< orphan*/  cr_iip; } ;
struct TYPE_4__ {int /*<<< orphan*/  pmsa_nat_bits; int /*<<< orphan*/ * pmsa_bank0_gr; int /*<<< orphan*/ * pmsa_bank1_gr; int /*<<< orphan*/  const* pmsa_gr; int /*<<< orphan*/  pmsa_rsc; int /*<<< orphan*/  pmsa_br0; int /*<<< orphan*/  pmsa_pr; int /*<<< orphan*/  pmsa_xfs; int /*<<< orphan*/  pmsa_xpsr; int /*<<< orphan*/  pmsa_xip; int /*<<< orphan*/  pmsa_ifs; int /*<<< orphan*/  pmsa_ipsr; int /*<<< orphan*/  pmsa_iip; } ;
typedef  TYPE_1__ pal_min_state_area_t ;
struct TYPE_5__ {scalar_t__ bn; scalar_t__ ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  copy_reg (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long*) ; 
 TYPE_2__* ia64_psr (struct pt_regs*) ; 

__attribute__((used)) static void
finish_pt_regs(struct pt_regs *regs, const pal_min_state_area_t *ms,
		unsigned long *nat)
{
	const u64 *bank;

	/* If ipsr.ic then use pmsa_{iip,ipsr,ifs}, else use
	 * pmsa_{xip,xpsr,xfs}
	 */
	if (ia64_psr(regs)->ic) {
		regs->cr_iip = ms->pmsa_iip;
		regs->cr_ipsr = ms->pmsa_ipsr;
		regs->cr_ifs = ms->pmsa_ifs;
	} else {
		regs->cr_iip = ms->pmsa_xip;
		regs->cr_ipsr = ms->pmsa_xpsr;
		regs->cr_ifs = ms->pmsa_xfs;
	}
	regs->pr = ms->pmsa_pr;
	regs->b0 = ms->pmsa_br0;
	regs->ar_rsc = ms->pmsa_rsc;
	copy_reg(&ms->pmsa_gr[1-1], ms->pmsa_nat_bits, &regs->r1, nat);
	copy_reg(&ms->pmsa_gr[2-1], ms->pmsa_nat_bits, &regs->r2, nat);
	copy_reg(&ms->pmsa_gr[3-1], ms->pmsa_nat_bits, &regs->r3, nat);
	copy_reg(&ms->pmsa_gr[8-1], ms->pmsa_nat_bits, &regs->r8, nat);
	copy_reg(&ms->pmsa_gr[9-1], ms->pmsa_nat_bits, &regs->r9, nat);
	copy_reg(&ms->pmsa_gr[10-1], ms->pmsa_nat_bits, &regs->r10, nat);
	copy_reg(&ms->pmsa_gr[11-1], ms->pmsa_nat_bits, &regs->r11, nat);
	copy_reg(&ms->pmsa_gr[12-1], ms->pmsa_nat_bits, &regs->r12, nat);
	copy_reg(&ms->pmsa_gr[13-1], ms->pmsa_nat_bits, &regs->r13, nat);
	copy_reg(&ms->pmsa_gr[14-1], ms->pmsa_nat_bits, &regs->r14, nat);
	copy_reg(&ms->pmsa_gr[15-1], ms->pmsa_nat_bits, &regs->r15, nat);
	if (ia64_psr(regs)->bn)
		bank = ms->pmsa_bank1_gr;
	else
		bank = ms->pmsa_bank0_gr;
	copy_reg(&bank[16-16], ms->pmsa_nat_bits, &regs->r16, nat);
	copy_reg(&bank[17-16], ms->pmsa_nat_bits, &regs->r17, nat);
	copy_reg(&bank[18-16], ms->pmsa_nat_bits, &regs->r18, nat);
	copy_reg(&bank[19-16], ms->pmsa_nat_bits, &regs->r19, nat);
	copy_reg(&bank[20-16], ms->pmsa_nat_bits, &regs->r20, nat);
	copy_reg(&bank[21-16], ms->pmsa_nat_bits, &regs->r21, nat);
	copy_reg(&bank[22-16], ms->pmsa_nat_bits, &regs->r22, nat);
	copy_reg(&bank[23-16], ms->pmsa_nat_bits, &regs->r23, nat);
	copy_reg(&bank[24-16], ms->pmsa_nat_bits, &regs->r24, nat);
	copy_reg(&bank[25-16], ms->pmsa_nat_bits, &regs->r25, nat);
	copy_reg(&bank[26-16], ms->pmsa_nat_bits, &regs->r26, nat);
	copy_reg(&bank[27-16], ms->pmsa_nat_bits, &regs->r27, nat);
	copy_reg(&bank[28-16], ms->pmsa_nat_bits, &regs->r28, nat);
	copy_reg(&bank[29-16], ms->pmsa_nat_bits, &regs->r29, nat);
	copy_reg(&bank[30-16], ms->pmsa_nat_bits, &regs->r30, nat);
	copy_reg(&bank[31-16], ms->pmsa_nat_bits, &regs->r31, nat);
}