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
struct captured_breakpoint_args {char* address; char* condition; int hardwareflag; int tempflag; int thread; int ignore_count; } ;
typedef  enum gdb_rc { ____Placeholder_gdb_rc } gdb_rc ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_MASK_ALL ; 
 int catch_errors (int /*<<< orphan*/ ,struct captured_breakpoint_args*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_captured_breakpoint ; 

enum gdb_rc
gdb_breakpoint (char *address, char *condition,
		int hardwareflag, int tempflag,
		int thread, int ignore_count)
{
  struct captured_breakpoint_args args;
  args.address = address;
  args.condition = condition;
  args.hardwareflag = hardwareflag;
  args.tempflag = tempflag;
  args.thread = thread;
  args.ignore_count = ignore_count;
  return catch_errors (do_captured_breakpoint, &args,
		       NULL, RETURN_MASK_ALL);
}