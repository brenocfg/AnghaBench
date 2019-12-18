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
 int /*<<< orphan*/  FATAL_EXIT_CODE ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  internal_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_operand_lossage (char*) ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strsignal (int) ; 
 scalar_t__ this_is_asm_operands ; 

__attribute__((used)) static void
crash_signal (int signo)
{
  signal (signo, SIG_DFL);

  /* If we crashed while processing an ASM statement, then be a little more
     graceful.  It's most likely the user's fault.  */
  if (this_is_asm_operands)
    {
      output_operand_lossage ("unrecoverable error");
      exit (FATAL_EXIT_CODE);
    }

  internal_error ("%s", strsignal (signo));
}