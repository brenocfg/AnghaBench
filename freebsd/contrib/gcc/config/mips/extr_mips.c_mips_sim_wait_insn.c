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
struct mips_sim {int dummy; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  mips_sim_wait_regs (struct mips_sim*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_sim_wait_units (struct mips_sim*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mips_sim_wait_insn (struct mips_sim *state, rtx insn)
{
  mips_sim_wait_regs (state, insn);
  mips_sim_wait_units (state, insn);
}