#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * tree ;
struct TYPE_3__ {int /*<<< orphan*/ * (* analyze_expr ) (int /*<<< orphan*/ **,int*,void*) ;} ;
struct TYPE_4__ {TYPE_1__ callgraph; } ;

/* Variables and functions */
#define  ADDR_EXPR 130 
 int /*<<< orphan*/  DECL_EXTERNAL (int /*<<< orphan*/ *) ; 
#define  FDESC_EXPR 129 
 int FUNCTION_DECL ; 
 int /*<<< orphan*/  IS_TYPE_OR_DECL_P (int /*<<< orphan*/ *) ; 
 unsigned int LAST_AND_UNUSED_TREE_CODE ; 
 int TREE_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_OPERAND (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_STATIC (int /*<<< orphan*/ *) ; 
#define  VAR_DECL 128 
 int /*<<< orphan*/  cgraph_mark_needed_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgraph_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cgraph_varpool_mark_needed_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgraph_varpool_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flag_unit_at_a_time ; 
 TYPE_2__ lang_hooks ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ **,int*,void*) ; 
 int /*<<< orphan*/ * stub2 (int /*<<< orphan*/ **,int*,void*) ; 

__attribute__((used)) static tree
record_reference (tree *tp, int *walk_subtrees, void *data)
{
  tree t = *tp;

  switch (TREE_CODE (t))
    {
    case VAR_DECL:
      /* ??? Really, we should mark this decl as *potentially* referenced
	 by this function and re-examine whether the decl is actually used
	 after rtl has been generated.  */
      if (TREE_STATIC (t) || DECL_EXTERNAL (t))
	{
	  cgraph_varpool_mark_needed_node (cgraph_varpool_node (t));
	  if (lang_hooks.callgraph.analyze_expr)
	    return lang_hooks.callgraph.analyze_expr (tp, walk_subtrees,
						      data);
	}
      break;

    case FDESC_EXPR:
    case ADDR_EXPR:
      if (flag_unit_at_a_time)
	{
	  /* Record dereferences to the functions.  This makes the
	     functions reachable unconditionally.  */
	  tree decl = TREE_OPERAND (*tp, 0);
	  if (TREE_CODE (decl) == FUNCTION_DECL)
	    cgraph_mark_needed_node (cgraph_node (decl));
	}
      break;

    default:
      /* Save some cycles by not walking types and declaration as we
	 won't find anything useful there anyway.  */
      if (IS_TYPE_OR_DECL_P (*tp))
	{
	  *walk_subtrees = 0;
	  break;
	}

      if ((unsigned int) TREE_CODE (t) >= LAST_AND_UNUSED_TREE_CODE)
	return lang_hooks.callgraph.analyze_expr (tp, walk_subtrees, data);
      break;
    }

  return NULL;
}