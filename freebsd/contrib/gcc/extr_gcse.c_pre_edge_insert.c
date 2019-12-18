#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct occr {int /*<<< orphan*/  deleted_p; struct occr* next; } ;
struct expr {scalar_t__ reaching_reg; int bitmap_index; struct occr* antic_occr; } ;
struct edge_list {int dummy; } ;
typedef  int /*<<< orphan*/  sbitmap ;
typedef  int /*<<< orphan*/  rtx ;
typedef  TYPE_1__* edge ;
typedef  TYPE_2__* basic_block ;
struct TYPE_14__ {int index; } ;
struct TYPE_13__ {scalar_t__ n_elems; } ;
struct TYPE_12__ {int size; int* elms; } ;
struct TYPE_11__ {int index; } ;
struct TYPE_10__ {int flags; } ;
typedef  int SBITMAP_ELT_TYPE ;

/* Variables and functions */
 int EDGE_ABNORMAL ; 
 TYPE_1__* INDEX_EDGE (struct edge_list*,int) ; 
 TYPE_2__* INDEX_EDGE_PRED_BB (struct edge_list*,int) ; 
 TYPE_7__* INDEX_EDGE_SUCC_BB (struct edge_list*,int) ; 
 scalar_t__ NULL_RTX ; 
 int NUM_EDGES (struct edge_list*) ; 
 scalar_t__ SBITMAP_ELT_BITS ; 
 int /*<<< orphan*/  SET_BIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_BIT (int /*<<< orphan*/ ,int) ; 
 scalar_t__ dump_file ; 
 TYPE_6__ expr_hash_table ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,int,...) ; 
 int /*<<< orphan*/  gcse_create_count ; 
 int /*<<< orphan*/  insert_insn_end_bb (struct expr*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_insn_on_edge (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_3__** pre_insert_map ; 
 int /*<<< orphan*/  process_insert_insn (struct expr*) ; 
 int /*<<< orphan*/ * sbitmap_vector_alloc (int,scalar_t__) ; 
 int /*<<< orphan*/  sbitmap_vector_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbitmap_vector_zero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  update_ld_motion_stores (struct expr*) ; 

__attribute__((used)) static int
pre_edge_insert (struct edge_list *edge_list, struct expr **index_map)
{
  int e, i, j, num_edges, set_size, did_insert = 0;
  sbitmap *inserted;

  /* Where PRE_INSERT_MAP is nonzero, we add the expression on that edge
     if it reaches any of the deleted expressions.  */

  set_size = pre_insert_map[0]->size;
  num_edges = NUM_EDGES (edge_list);
  inserted = sbitmap_vector_alloc (num_edges, expr_hash_table.n_elems);
  sbitmap_vector_zero (inserted, num_edges);

  for (e = 0; e < num_edges; e++)
    {
      int indx;
      basic_block bb = INDEX_EDGE_PRED_BB (edge_list, e);

      for (i = indx = 0; i < set_size; i++, indx += SBITMAP_ELT_BITS)
	{
	  SBITMAP_ELT_TYPE insert = pre_insert_map[e]->elms[i];

	  for (j = indx; insert && j < (int) expr_hash_table.n_elems; j++, insert >>= 1)
	    if ((insert & 1) != 0 && index_map[j]->reaching_reg != NULL_RTX)
	      {
		struct expr *expr = index_map[j];
		struct occr *occr;

		/* Now look at each deleted occurrence of this expression.  */
		for (occr = expr->antic_occr; occr != NULL; occr = occr->next)
		  {
		    if (! occr->deleted_p)
		      continue;

		    /* Insert this expression on this edge if it would
		       reach the deleted occurrence in BB.  */
		    if (!TEST_BIT (inserted[e], j))
		      {
			rtx insn;
			edge eg = INDEX_EDGE (edge_list, e);

			/* We can't insert anything on an abnormal and
			   critical edge, so we insert the insn at the end of
			   the previous block. There are several alternatives
			   detailed in Morgans book P277 (sec 10.5) for
			   handling this situation.  This one is easiest for
			   now.  */

			if (eg->flags & EDGE_ABNORMAL)
			  insert_insn_end_bb (index_map[j], bb, 0);
			else
			  {
			    insn = process_insert_insn (index_map[j]);
			    insert_insn_on_edge (insn, eg);
			  }

			if (dump_file)
			  {
			    fprintf (dump_file, "PRE/HOIST: edge (%d,%d), ",
				     bb->index,
				     INDEX_EDGE_SUCC_BB (edge_list, e)->index);
			    fprintf (dump_file, "copy expression %d\n",
				     expr->bitmap_index);
			  }

			update_ld_motion_stores (expr);
			SET_BIT (inserted[e], j);
			did_insert = 1;
			gcse_create_count++;
		      }
		  }
	      }
	}
    }

  sbitmap_vector_free (inserted);
  return did_insert;
}