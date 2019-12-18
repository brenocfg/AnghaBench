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
typedef  int /*<<< orphan*/ * tree ;
typedef  int /*<<< orphan*/  c_pretty_printer ;

/* Variables and functions */
 int /*<<< orphan*/  dump_generic_node (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pp_base (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_indentation (int /*<<< orphan*/ *) ; 
 scalar_t__ pp_needs_newline (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_newline_and_indent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
pp_c_statement (c_pretty_printer *pp, tree stmt)
{
  if (stmt == NULL)
    return;

  if (pp_needs_newline (pp))
    pp_newline_and_indent (pp, 0);

  dump_generic_node (pp_base (pp), stmt, pp_indentation (pp), 0, true);
}