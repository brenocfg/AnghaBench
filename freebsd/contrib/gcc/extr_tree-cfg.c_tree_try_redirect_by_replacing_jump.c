#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_1__* edge ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  TYPE_2__* basic_block ;
struct TYPE_13__ {int /*<<< orphan*/  succs; } ;
struct TYPE_12__ {int /*<<< orphan*/  flags; TYPE_2__* dest; TYPE_2__* src; } ;

/* Variables and functions */
 scalar_t__ COND_EXPR ; 
 int EDGE_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDGE_FALLTHRU ; 
 TYPE_1__* EDGE_SUCC (TYPE_2__*,int) ; 
 scalar_t__ SWITCH_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ bsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_last (TYPE_2__*) ; 
 int /*<<< orphan*/  bsi_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bsi_stmt (int /*<<< orphan*/ ) ; 
 TYPE_1__* ssa_redirect_edge (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static edge
tree_try_redirect_by_replacing_jump (edge e, basic_block target)
{
  basic_block src = e->src;
  block_stmt_iterator b;
  tree stmt;

  /* We can replace or remove a complex jump only when we have exactly
     two edges.  */
  if (EDGE_COUNT (src->succs) != 2
      /* Verify that all targets will be TARGET.  Specifically, the
	 edge that is not E must also go to TARGET.  */
      || EDGE_SUCC (src, EDGE_SUCC (src, 0) == e)->dest != target)
    return NULL;

  b = bsi_last (src);
  if (bsi_end_p (b))
    return NULL;
  stmt = bsi_stmt (b);

  if (TREE_CODE (stmt) == COND_EXPR
      || TREE_CODE (stmt) == SWITCH_EXPR)
    {
      bsi_remove (&b, true);
      e = ssa_redirect_edge (e, target);
      e->flags = EDGE_FALLTHRU;
      return e;
    }

  return NULL;
}