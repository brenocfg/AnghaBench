#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct cgraph_node {struct cgraph_node* next_clone; } ;
struct cgraph_edge {int dummy; } ;
struct TYPE_12__ {int transform_call_graph_edges; scalar_t__ eh_region_offset; scalar_t__ eh_region; int /*<<< orphan*/  src_cfun; struct cgraph_node* dst_node; struct cgraph_node* src_node; } ;
typedef  TYPE_2__ copy_body_data ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  TYPE_3__* basic_block ;
struct TYPE_13__ {int count; int frequency; TYPE_1__* prev_bb; } ;
struct TYPE_11__ {scalar_t__ aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSI_NEW_STMT ; 
#define  CB_CGE_DUPLICATE 130 
#define  CB_CGE_MOVE 129 
#define  CB_CGE_MOVE_CLONES 128 
 scalar_t__ MODIFY_EXPR ; 
 scalar_t__ NOP_EXPR ; 
 int REG_BR_PROB_BASE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  add_stmt_to_eh_region (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_insert_after (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsi_start (TYPE_3__*) ; 
 scalar_t__ bsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgraph_clone_edge (struct cgraph_edge*,struct cgraph_node*,scalar_t__,int,int,int) ; 
 struct cgraph_edge* cgraph_edge (struct cgraph_node*,scalar_t__) ; 
 int /*<<< orphan*/  cgraph_set_call_stmt (struct cgraph_edge*,scalar_t__) ; 
 int /*<<< orphan*/  copy_body_r ; 
 TYPE_3__* create_basic_block (int /*<<< orphan*/ *,void*,TYPE_3__*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ get_call_expr_in (scalar_t__) ; 
 scalar_t__ get_callee_fndecl (scalar_t__) ; 
 int /*<<< orphan*/  gimplify_stmt (scalar_t__*) ; 
 int /*<<< orphan*/  is_gimple_val (scalar_t__) ; 
 int lookup_stmt_eh_region_fn (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ tree_could_throw_p (scalar_t__) ; 
 int /*<<< orphan*/  walk_tree (scalar_t__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static basic_block
copy_bb (copy_body_data *id, basic_block bb, int frequency_scale, int count_scale)
{
  block_stmt_iterator bsi, copy_bsi;
  basic_block copy_basic_block;

  /* create_basic_block() will append every new block to
     basic_block_info automatically.  */
  copy_basic_block = create_basic_block (NULL, (void *) 0,
                                         (basic_block) bb->prev_bb->aux);
  copy_basic_block->count = bb->count * count_scale / REG_BR_PROB_BASE;
  copy_basic_block->frequency = (bb->frequency
				     * frequency_scale / REG_BR_PROB_BASE);
  copy_bsi = bsi_start (copy_basic_block);

  for (bsi = bsi_start (bb);
       !bsi_end_p (bsi); bsi_next (&bsi))
    {
      tree stmt = bsi_stmt (bsi);
      tree orig_stmt = stmt;

      walk_tree (&stmt, copy_body_r, id, NULL);

      /* RETURN_EXPR might be removed,
         this is signalled by making stmt pointer NULL.  */
      if (stmt)
	{
	  tree call, decl;

	  /* With return slot optimization we can end up with
	     non-gimple (foo *)&this->m, fix that here.  */
	  if (TREE_CODE (stmt) == MODIFY_EXPR
	      && TREE_CODE (TREE_OPERAND (stmt, 1)) == NOP_EXPR
	      && !is_gimple_val (TREE_OPERAND (TREE_OPERAND (stmt, 1), 0)))
	    gimplify_stmt (&stmt);

          bsi_insert_after (&copy_bsi, stmt, BSI_NEW_STMT);
	  call = get_call_expr_in (stmt);
	  /* We're duplicating a CALL_EXPR.  Find any corresponding
	     callgraph edges and update or duplicate them.  */
	  if (call && (decl = get_callee_fndecl (call)))
	    {
	      struct cgraph_node *node;
	      struct cgraph_edge *edge;
	     
	      switch (id->transform_call_graph_edges)
		{
		case CB_CGE_DUPLICATE:
		  edge = cgraph_edge (id->src_node, orig_stmt);
		  if (edge)
		    cgraph_clone_edge (edge, id->dst_node, stmt,
				       REG_BR_PROB_BASE, 1, true);
		  break;

		case CB_CGE_MOVE_CLONES:
		  for (node = id->dst_node->next_clone;
		       node;
		       node = node->next_clone)
		    {
		      edge = cgraph_edge (node, orig_stmt);
		      gcc_assert (edge);
		      cgraph_set_call_stmt (edge, stmt);
		    }
		  /* FALLTHRU */

		case CB_CGE_MOVE:
		  edge = cgraph_edge (id->dst_node, orig_stmt);
		  if (edge)
		    cgraph_set_call_stmt (edge, stmt);
		  break;

		default:
		  gcc_unreachable ();
		}
	    }
	  /* If you think we can abort here, you are wrong.
	     There is no region 0 in tree land.  */
	  gcc_assert (lookup_stmt_eh_region_fn (id->src_cfun, orig_stmt)
		      != 0);

	  if (tree_could_throw_p (stmt))
	    {
	      int region = lookup_stmt_eh_region_fn (id->src_cfun, orig_stmt);
	      /* Add an entry for the copied tree in the EH hashtable.
		 When cloning or versioning, use the hashtable in
		 cfun, and just copy the EH number.  When inlining, use the
		 hashtable in the caller, and adjust the region number.  */
	      if (region > 0)
		add_stmt_to_eh_region (stmt, region + id->eh_region_offset);

	      /* If this tree doesn't have a region associated with it,
		 and there is a "current region,"
		 then associate this tree with the current region
		 and add edges associated with this region.  */
	      if ((lookup_stmt_eh_region_fn (id->src_cfun,
					     orig_stmt) <= 0
		   && id->eh_region > 0)
		  && tree_could_throw_p (stmt))
		add_stmt_to_eh_region (stmt, id->eh_region);
	    }
	}
    }
  return copy_basic_block;
}