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
struct captured_main_args {int argc; char** argv; int /*<<< orphan*/  interpreter_p; scalar_t__ use_windows; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTERP_CONSOLE ; 
 int gdb_main (struct captured_main_args*) ; 
 int /*<<< orphan*/  memset (struct captured_main_args*,int /*<<< orphan*/ ,int) ; 

int
main (int argc, char **argv)
{
  struct captured_main_args args;
  memset (&args, 0, sizeof args);
  args.argc = argc;
  args.argv = argv;
  args.use_windows = 0;
  args.interpreter_p = INTERP_CONSOLE;
  return gdb_main (&args);
}