#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  pretty_printer ;
typedef  TYPE_1__* basic_block ;
struct TYPE_4__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 scalar_t__ LABEL_EXPR ; 
 int /*<<< orphan*/  LABEL_EXPR_LABEL (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  dump_generic_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ first_stmt (TYPE_1__*) ; 
 int /*<<< orphan*/  pp_decimal_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_semicolon (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_string (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
pp_cfg_jump (pretty_printer *buffer, basic_block bb)
{
  tree stmt;

  stmt = first_stmt (bb);

  pp_string (buffer, "goto <bb ");
  pp_decimal_int (buffer, bb->index);
  pp_string (buffer, ">");
  if (stmt && TREE_CODE (stmt) == LABEL_EXPR)
    {
      pp_string (buffer, " (");
      dump_generic_node (buffer, LABEL_EXPR_LABEL (stmt), 0, 0, false);
      pp_string (buffer, ")");
    }
  pp_semicolon (buffer);
}