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
 int /*<<< orphan*/  BBA_BP ; 
 int /*<<< orphan*/  BBA_GCA ; 
 int BBA_GCA_ARXERRB ; 
 int /*<<< orphan*/  BBA_INIT_BP ; 
 int /*<<< orphan*/  BBA_INIT_RHBP ; 
 int /*<<< orphan*/  BBA_INIT_RRP ; 
 int /*<<< orphan*/  BBA_INIT_RWP ; 
 int /*<<< orphan*/  BBA_INIT_TLBP ; 
 int /*<<< orphan*/  BBA_MISC2 ; 
 int BBA_MISC2_AUTORCVR ; 
 int /*<<< orphan*/  BBA_NCRA ; 
 int BBA_NCRA_SR ; 
 int /*<<< orphan*/  BBA_NCRB ; 
 int BBA_NCRB_AB ; 
 int BBA_NCRB_CA ; 
 int /*<<< orphan*/  BBA_RHBP ; 
 int /*<<< orphan*/  BBA_RRP ; 
 int /*<<< orphan*/  BBA_RWP ; 
 int /*<<< orphan*/  BBA_TLBP ; 
 int /*<<< orphan*/  bba_out12 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bba_out8 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __bba_recv_init()
{
	bba_out8(BBA_NCRB,(BBA_NCRB_CA|BBA_NCRB_AB));
	bba_out8(BBA_MISC2,(BBA_MISC2_AUTORCVR));

	bba_out12(BBA_TLBP, BBA_INIT_TLBP);
	bba_out12(BBA_BP,BBA_INIT_BP);
	bba_out12(BBA_RWP,BBA_INIT_RWP);
	bba_out12(BBA_RRP,BBA_INIT_RRP);
	bba_out12(BBA_RHBP,BBA_INIT_RHBP);

	bba_out8(BBA_GCA,BBA_GCA_ARXERRB);
	bba_out8(BBA_NCRA,BBA_NCRA_SR);
}