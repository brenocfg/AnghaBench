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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  pretty_printer ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  INDENT (int) ; 
 scalar_t__ LABEL_EXPR ; 
 int TDF_BLOCKS ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsi_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_bb_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dump_bb_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dump_generic_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  dump_implicit_edges (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dump_phi_nodes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pp_newline (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dump_generic_bb_buff (pretty_printer *buffer, basic_block bb,
		      int indent, int flags)
{
  block_stmt_iterator bsi;
  tree stmt;
  int label_indent = indent - 2;

  if (label_indent < 0)
    label_indent = 0;

  dump_bb_header (buffer, bb, indent, flags);

  dump_phi_nodes (buffer, bb, indent, flags);

  for (bsi = bsi_start (bb); !bsi_end_p (bsi); bsi_next (&bsi))
    {
      int curr_indent;

      stmt = bsi_stmt (bsi);

      curr_indent = TREE_CODE (stmt) == LABEL_EXPR ? label_indent : indent;

      INDENT (curr_indent);
      dump_generic_node (buffer, stmt, curr_indent, flags, true);
      pp_newline (buffer);
    }

  dump_implicit_edges (buffer, bb, indent, flags);

  if (flags & TDF_BLOCKS)
    dump_bb_end (buffer, bb, indent, flags);
}