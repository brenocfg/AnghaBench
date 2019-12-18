#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* edge ;
typedef  TYPE_2__* basic_block ;
struct TYPE_14__ {int flags; } ;
struct TYPE_13__ {int /*<<< orphan*/  succs; } ;
struct TYPE_12__ {int flags; TYPE_2__* dest; TYPE_2__* src; } ;

/* Variables and functions */
 int /*<<< orphan*/  BB_END (TYPE_2__*) ; 
 int EDGE_COUNT (int /*<<< orphan*/ ) ; 
 int EDGE_IRREDUCIBLE_LOOP ; 
 TYPE_1__* EDGE_SUCC (TYPE_2__*,int) ; 
 TYPE_2__* EXIT_BLOCK_PTR ; 
 int /*<<< orphan*/  any_condjump_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  redirect_edge_and_branch (TYPE_1__*,TYPE_2__*) ; 
 TYPE_3__* single_succ_edge (TYPE_2__*) ; 

__attribute__((used)) static bool
loop_delete_branch_edge (edge e, int really_delete)
{
  basic_block src = e->src;
  basic_block newdest;
  int irr;
  edge snd;

  gcc_assert (EDGE_COUNT (src->succs) > 1);

  /* Cannot handle more than two exit edges.  */
  if (EDGE_COUNT (src->succs) > 2)
    return false;
  /* And it must be just a simple branch.  */
  if (!any_condjump_p (BB_END (src)))
    return false;

  snd = e == EDGE_SUCC (src, 0) ? EDGE_SUCC (src, 1) : EDGE_SUCC (src, 0);
  newdest = snd->dest;
  if (newdest == EXIT_BLOCK_PTR)
    return false;

  /* Hopefully the above conditions should suffice.  */
  if (!really_delete)
    return true;

  /* Redirecting behaves wrongly wrto this flag.  */
  irr = snd->flags & EDGE_IRREDUCIBLE_LOOP;

  if (!redirect_edge_and_branch (e, newdest))
    return false;
  single_succ_edge (src)->flags &= ~EDGE_IRREDUCIBLE_LOOP;
  single_succ_edge (src)->flags |= irr;

  return true;
}