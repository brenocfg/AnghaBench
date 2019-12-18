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
struct captured_parse_breakpoint_args {int /*<<< orphan*/  not_found_ptr; int /*<<< orphan*/  addr_string_p; int /*<<< orphan*/  sals_p; int /*<<< orphan*/  arg_p; } ;

/* Variables and functions */
 int GDB_RC_OK ; 
 int /*<<< orphan*/  parse_breakpoint_sals (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
do_captured_parse_breakpoint (struct ui_out *ui, void *data)
{
  struct captured_parse_breakpoint_args *args = data;
  
  parse_breakpoint_sals (args->arg_p, args->sals_p, args->addr_string_p, 
		         args->not_found_ptr);

  return GDB_RC_OK;
}