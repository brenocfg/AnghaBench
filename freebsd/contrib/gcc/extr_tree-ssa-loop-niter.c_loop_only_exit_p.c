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
typedef  scalar_t__ tree ;
struct loop {scalar_t__ single_exit; unsigned int num_nodes; } ;
typedef  scalar_t__ edge ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 scalar_t__ TREE_SIDE_EFFECTS (scalar_t__) ; 
 int /*<<< orphan*/  bsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsi_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ get_call_expr_in (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_loop_body (struct loop*) ; 

__attribute__((used)) static bool
loop_only_exit_p (struct loop *loop, edge exit)
{
  basic_block *body;
  block_stmt_iterator bsi;
  unsigned i;
  tree call;

  if (exit != loop->single_exit)
    return false;

  body = get_loop_body (loop);
  for (i = 0; i < loop->num_nodes; i++)
    {
      for (bsi = bsi_start (body[0]); !bsi_end_p (bsi); bsi_next (&bsi))
	{
	  call = get_call_expr_in (bsi_stmt (bsi));
	  if (call && TREE_SIDE_EFFECTS (call))
	    {
	      free (body);
	      return false;
	    }
	}
    }

  free (body);
  return true;
}