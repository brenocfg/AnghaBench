#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct mem_ref_loc {int /*<<< orphan*/  stmt; struct mem_ref_loc* next; } ;
struct loop {int num; } ;
struct lim_aux_data {int dummy; } ;
struct fmt_data {struct loop* orig_loop; struct loop* loop; } ;
typedef  int /*<<< orphan*/  edge ;
struct TYPE_6__ {int sm_done; struct loop* tgt_loop; struct loop* max_loop; } ;
struct TYPE_4__ {int /*<<< orphan*/  aux; } ;
struct TYPE_5__ {TYPE_1__ common; } ;

/* Variables and functions */
 TYPE_3__* LIM_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MODIFY_EXPR ; 
 int TDF_DETAILS ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_insert_on_edge (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  for_each_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct fmt_data*) ; 
 int /*<<< orphan*/  force_move_till ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 int /*<<< orphan*/  get_lsm_tmp_name (int /*<<< orphan*/ ) ; 
 TYPE_2__* get_stmt_ann (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loop_latch_edge (struct loop*) ; 
 int /*<<< orphan*/  make_rename_temp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_generic_expr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rewrite_mem_refs (int /*<<< orphan*/ ,struct mem_ref_loc*) ; 
 int /*<<< orphan*/  unshare_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  void_type_node ; 
 int /*<<< orphan*/  xcalloc (int,int) ; 

__attribute__((used)) static void
schedule_sm (struct loop *loop, edge *exits, unsigned n_exits, tree ref,
	     struct mem_ref_loc *mem_refs)
{
  struct mem_ref_loc *aref;
  tree tmp_var;
  unsigned i;
  tree load, store;
  struct fmt_data fmt_data;

  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "Executing store motion of ");
      print_generic_expr (dump_file, ref, 0);
      fprintf (dump_file, " from loop %d\n", loop->num);
    }

  tmp_var = make_rename_temp (TREE_TYPE (ref),
			      get_lsm_tmp_name (ref));

  fmt_data.loop = loop;
  fmt_data.orig_loop = loop;
  for_each_index (&ref, force_move_till, &fmt_data);

  rewrite_mem_refs (tmp_var, mem_refs);
  for (aref = mem_refs; aref; aref = aref->next)
    if (LIM_DATA (aref->stmt))
      LIM_DATA (aref->stmt)->sm_done = true;

  /* Emit the load & stores.  */
  load = build2 (MODIFY_EXPR, void_type_node, tmp_var, ref);
  get_stmt_ann (load)->common.aux = xcalloc (1, sizeof (struct lim_aux_data));
  LIM_DATA (load)->max_loop = loop;
  LIM_DATA (load)->tgt_loop = loop;

  /* Put this into the latch, so that we are sure it will be processed after
     all dependencies.  */
  bsi_insert_on_edge (loop_latch_edge (loop), load);

  for (i = 0; i < n_exits; i++)
    {
      store = build2 (MODIFY_EXPR, void_type_node,
		      unshare_expr (ref), tmp_var);
      bsi_insert_on_edge (exits[i], store);
    }
}