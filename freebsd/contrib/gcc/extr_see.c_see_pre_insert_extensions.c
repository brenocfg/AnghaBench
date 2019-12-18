#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct see_pre_extension_expr {int bitmap_index; int /*<<< orphan*/  se_insn; } ;
typedef  int /*<<< orphan*/ * rtx ;
typedef  TYPE_1__* edge ;
typedef  TYPE_2__* basic_block ;
struct TYPE_12__ {int index; } ;
struct TYPE_11__ {int size; int* elms; } ;
struct TYPE_10__ {int index; } ;
struct TYPE_9__ {int flags; } ;
typedef  int SBITMAP_ELT_TYPE ;

/* Variables and functions */
 int EDGE_ABNORMAL ; 
 TYPE_1__* INDEX_EDGE (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* INDEX_EDGE_PRED_BB (int /*<<< orphan*/ ,int) ; 
 TYPE_6__* INDEX_EDGE_SUCC_BB (int /*<<< orphan*/ ,int) ; 
 scalar_t__ INSN_P (int /*<<< orphan*/ *) ; 
 int INSN_UID (int /*<<< orphan*/ *) ; 
 int NUM_EDGES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 scalar_t__ SBITMAP_ELT_BITS ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  edge_list ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_sequence () ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,int,...) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/ * get_insns () ; 
 size_t htab_elements (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * insert_insn_end_bb_new (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  insert_insn_on_edge (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_3__** pre_insert_map ; 
 int /*<<< orphan*/  see_pre_extension_hash ; 
 int /*<<< orphan*/  start_sequence () ; 

__attribute__((used)) static bool
see_pre_insert_extensions (struct see_pre_extension_expr **index_map)
{
  int num_edges = NUM_EDGES (edge_list);
  int set_size = pre_insert_map[0]->size;
  size_t pre_extension_num = htab_elements (see_pre_extension_hash);

  int did_insert = 0;
  int e;
  int i;
  int j;

  for (e = 0; e < num_edges; e++)
    {
      int indx;
      basic_block bb = INDEX_EDGE_PRED_BB (edge_list, e);

      for (i = indx = 0; i < set_size; i++, indx += SBITMAP_ELT_BITS)
	{
	  SBITMAP_ELT_TYPE insert = pre_insert_map[e]->elms[i];

	  for (j = indx; insert && j < (int) pre_extension_num;
	       j++, insert >>= 1)
	    if (insert & 1)
	      {
		struct see_pre_extension_expr *expr = index_map[j];
		int idx = expr->bitmap_index;
		rtx se_insn = NULL;
		edge eg = INDEX_EDGE (edge_list, e);

		start_sequence ();
		emit_insn (PATTERN (expr->se_insn));
		se_insn = get_insns ();
		end_sequence ();

		if (eg->flags & EDGE_ABNORMAL)
		  {
		    rtx new_insn = NULL;

		    new_insn = insert_insn_end_bb_new (se_insn, bb);
		    gcc_assert (new_insn && INSN_P (new_insn));

		    if (dump_file)
		      {
			fprintf (dump_file,
				 "PRE: end of bb %d, insn %d, ",
				 bb->index, INSN_UID (new_insn));
			fprintf (dump_file,
				 "inserting expression %d\n", idx);
		      }
		  }
		else
		  {
		    insert_insn_on_edge (se_insn, eg);

		    if (dump_file)
		      {
			fprintf (dump_file, "PRE: edge (%d,%d), ",
				 bb->index,
				 INDEX_EDGE_SUCC_BB (edge_list, e)->index);
			fprintf (dump_file, "inserting expression %d\n", idx);
		      }
		  }
		did_insert = true;
	      }
	}
    }
  return did_insert;
}