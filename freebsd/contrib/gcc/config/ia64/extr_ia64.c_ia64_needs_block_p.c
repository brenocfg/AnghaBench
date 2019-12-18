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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 size_t INSN_UID (int /*<<< orphan*/ ) ; 
 int SPEC_GEN_CHECK_MUTATION_OFFSET ; 
 int SPEC_GEN_S ; 
 int SPEC_N ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int* spec_check_no ; 

__attribute__((used)) static bool
ia64_needs_block_p (rtx insn)
{
  int check_no;

  check_no = spec_check_no[INSN_UID(insn)] - 1;
  gcc_assert (0 <= check_no && check_no < SPEC_GEN_CHECK_MUTATION_OFFSET);

  return ((SPEC_GEN_S <= check_no && check_no < SPEC_GEN_S + SPEC_N)
	  || (4 * SPEC_N <= check_no && check_no < 4 * SPEC_N + SPEC_N));
}