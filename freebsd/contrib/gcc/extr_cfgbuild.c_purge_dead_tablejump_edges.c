#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * rtx ;
typedef  int /*<<< orphan*/  rtvec ;
typedef  int /*<<< orphan*/  edge_iterator ;
typedef  TYPE_1__* edge ;
typedef  TYPE_2__* basic_block ;
struct TYPE_8__ {int /*<<< orphan*/  succs; } ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  dest; } ;

/* Variables and functions */
 scalar_t__ ADDR_VEC ; 
 int /*<<< orphan*/ * BB_END (TYPE_2__*) ; 
 int BLOCK_USED_BY_TABLEJUMP ; 
 int EDGE_ABNORMAL ; 
 int EDGE_EH ; 
 size_t FULL_STATE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_NUM_ELEM (int /*<<< orphan*/ ) ; 
 scalar_t__ IF_THEN_ELSE ; 
 scalar_t__ LABEL_REF ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RTVEC_ELT (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SET_DEST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SET_STATE (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVEC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ei_next (int /*<<< orphan*/ *) ; 
 TYPE_1__* ei_safe_edge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ei_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_tablejump_edge (int /*<<< orphan*/ ) ; 
 scalar_t__ pc_rtx ; 
 int /*<<< orphan*/  remove_edge (TYPE_1__*) ; 
 int /*<<< orphan*/ * single_set (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
purge_dead_tablejump_edges (basic_block bb, rtx table)
{
  rtx insn = BB_END (bb), tmp;
  rtvec vec;
  int j;
  edge_iterator ei;
  edge e;

  if (GET_CODE (PATTERN (table)) == ADDR_VEC)
    vec = XVEC (PATTERN (table), 0);
  else
    vec = XVEC (PATTERN (table), 1);

  for (j = GET_NUM_ELEM (vec) - 1; j >= 0; --j)
    mark_tablejump_edge (XEXP (RTVEC_ELT (vec, j), 0));

  /* Some targets (eg, ARM) emit a conditional jump that also
     contains the out-of-range target.  Scan for these and
     add an edge if necessary.  */
  if ((tmp = single_set (insn)) != NULL
       && SET_DEST (tmp) == pc_rtx
       && GET_CODE (SET_SRC (tmp)) == IF_THEN_ELSE
       && GET_CODE (XEXP (SET_SRC (tmp), 2)) == LABEL_REF)
    mark_tablejump_edge (XEXP (XEXP (SET_SRC (tmp), 2), 0));

  for (ei = ei_start (bb->succs); (e = ei_safe_edge (ei)); )
    {
      if (FULL_STATE (e->dest) & BLOCK_USED_BY_TABLEJUMP)
	SET_STATE (e->dest, FULL_STATE (e->dest)
			    & ~(size_t) BLOCK_USED_BY_TABLEJUMP);
      else if (!(e->flags & (EDGE_ABNORMAL | EDGE_EH)))
	{
	  remove_edge (e);
	  continue;
	}
      ei_next (&ei);
    }
}