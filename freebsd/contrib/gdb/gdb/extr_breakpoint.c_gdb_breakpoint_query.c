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
struct ui_out {int dummy; } ;
struct captured_breakpoint_query_args {int bnum; } ;
typedef  enum gdb_rc { ____Placeholder_gdb_rc } gdb_rc ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_MASK_ALL ; 
 int catch_exceptions (struct ui_out*,int /*<<< orphan*/ ,struct captured_breakpoint_query_args*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_captured_breakpoint_query ; 

enum gdb_rc
gdb_breakpoint_query (struct ui_out *uiout, int bnum)
{
  struct captured_breakpoint_query_args args;
  args.bnum = bnum;
  /* For the moment we don't trust print_one_breakpoint() to not throw
     an error. */
  return catch_exceptions (uiout, do_captured_breakpoint_query, &args,
			   NULL, RETURN_MASK_ALL);
}