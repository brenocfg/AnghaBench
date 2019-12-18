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
typedef  enum target_signal { ____Placeholder_target_signal } target_signal ;

/* Variables and functions */
 int TARGET_SIGNAL_UNKNOWN ; 

__attribute__((used)) static enum target_signal
mips_signal_from_protocol (int sig)
{
  /* We allow a few more signals than the IDT board actually returns, on
     the theory that there is at least *some* hope that perhaps the numbering
     for these signals is widely agreed upon.  */
  if (sig <= 0
      || sig > 31)
    return TARGET_SIGNAL_UNKNOWN;

  /* Don't want to use target_signal_from_host because we are converting
     from MIPS signal numbers, not host ones.  Our internal numbers
     match the MIPS numbers for the signals the board can return, which
     are: SIGINT, SIGSEGV, SIGBUS, SIGILL, SIGFPE, SIGTRAP.  */
  return (enum target_signal) sig;
}