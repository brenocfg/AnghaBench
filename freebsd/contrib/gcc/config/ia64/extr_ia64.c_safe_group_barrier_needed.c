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
struct reg_write_state {int dummy; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int NUM_REGS ; 
 int first_instruction ; 
 int group_barrier_needed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct reg_write_state*,struct reg_write_state*,int) ; 
 struct reg_write_state* rws_sum ; 

__attribute__((used)) static int
safe_group_barrier_needed (rtx insn)
{
  struct reg_write_state rws_saved[NUM_REGS];
  int saved_first_instruction;
  int t;

  memcpy (rws_saved, rws_sum, NUM_REGS * sizeof *rws_saved);
  saved_first_instruction = first_instruction;

  t = group_barrier_needed (insn);

  memcpy (rws_sum, rws_saved, NUM_REGS * sizeof *rws_saved);
  first_instruction = saved_first_instruction;

  return t;
}