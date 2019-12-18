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
typedef  scalar_t__ rtx ;
typedef  int HOST_WIDE_INT ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ADDR_REGS ; 
 size_t FIRST_PSEUDO_REGISTER ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 char* HOST_WIDE_INT_PRINT_DEC ; 
 scalar_t__ REG ; 
 size_t REGNO (scalar_t__) ; 
 scalar_t__ REGNO_REG_CLASS (size_t) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 char** reg_names ; 
 int /*<<< orphan*/  s390_decompose_shift_count (scalar_t__,scalar_t__*,int*) ; 

__attribute__((used)) static void
print_shift_count_operand (FILE *file, rtx op)
{
  HOST_WIDE_INT offset;
  rtx base;

  /* Extract base register and offset.  */
  if (!s390_decompose_shift_count (op, &base, &offset))
    gcc_unreachable ();

  /* Sanity check.  */
  if (base)
    {
      gcc_assert (GET_CODE (base) == REG);
      gcc_assert (REGNO (base) < FIRST_PSEUDO_REGISTER);
      gcc_assert (REGNO_REG_CLASS (REGNO (base)) == ADDR_REGS);
    }

  /* Offsets are constricted to twelve bits.  */
  fprintf (file, HOST_WIDE_INT_PRINT_DEC, offset & ((1 << 12) - 1));
  if (base)
    fprintf (file, "(%s)", reg_names[REGNO (base)]);
}