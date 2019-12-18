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
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  error_no_arg (char*) ; 
 int get_number (char**) ; 
 int /*<<< orphan*/  longest_to_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_and_eval (char*) ; 
 int /*<<< orphan*/  printf_filtered (char*) ; 
 int /*<<< orphan*/  set_ignore_count (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  value_as_long (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ignore_command (char *args, int from_tty)
{
  char *p = args;
  int num;

  if (p == 0)
    error_no_arg ("a breakpoint number");

  num = get_number (&p);
  if (num == 0)
    error ("bad breakpoint number: '%s'", args);
  if (*p == 0)
    error ("Second argument (specified ignore-count) is missing.");

  set_ignore_count (num,
		    longest_to_int (value_as_long (parse_and_eval (p))),
		    from_tty);
  if (from_tty)
    printf_filtered ("\n");
}