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
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  exit_failure ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int) ; 
 char* program_error_message ; 
 char* program_name ; 
 int /*<<< orphan*/  segv_action (int) ; 
 char* stack_overflow_message ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
die (int signo)
{
  char const *message;
  segv_action (signo);
  message = signo ? program_error_message : stack_overflow_message;
  write (STDERR_FILENO, program_name, strlen (program_name));
  write (STDERR_FILENO, ": ", 2);
  write (STDERR_FILENO, message, strlen (message));
  write (STDERR_FILENO, "\n", 1);
  if (! signo)
    _exit (exit_failure);
  kill (getpid (), signo);
  abort ();
}