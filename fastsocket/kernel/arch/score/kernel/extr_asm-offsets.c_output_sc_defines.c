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
 int /*<<< orphan*/  BLANK () ; 
 int /*<<< orphan*/  COMMENT (char*) ; 
 int /*<<< orphan*/  OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_ECR ; 
 int /*<<< orphan*/  SC_EMA ; 
 int /*<<< orphan*/  SC_MDCEH ; 
 int /*<<< orphan*/  SC_MDCEL ; 
 int /*<<< orphan*/  SC_PC ; 
 int /*<<< orphan*/  SC_PSR ; 
 int /*<<< orphan*/  SC_REGS ; 
 int /*<<< orphan*/  sc_ecr ; 
 int /*<<< orphan*/  sc_ema ; 
 int /*<<< orphan*/  sc_mdceh ; 
 int /*<<< orphan*/  sc_mdcel ; 
 int /*<<< orphan*/  sc_pc ; 
 int /*<<< orphan*/  sc_psr ; 
 int /*<<< orphan*/  sc_regs ; 
 int /*<<< orphan*/  sigcontext ; 

void output_sc_defines(void)
{
	COMMENT("Linux sigcontext offsets.");
	OFFSET(SC_REGS, sigcontext, sc_regs);
	OFFSET(SC_MDCEH, sigcontext, sc_mdceh);
	OFFSET(SC_MDCEL, sigcontext, sc_mdcel);
	OFFSET(SC_PC, sigcontext, sc_pc);
	OFFSET(SC_PSR, sigcontext, sc_psr);
	OFFSET(SC_ECR, sigcontext, sc_ecr);
	OFFSET(SC_EMA, sigcontext, sc_ema);
	BLANK();
}