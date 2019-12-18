#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  TYPE_1__* priority_info ;
struct TYPE_3__ {int initializations_p; int destructions_p; } ;

/* Variables and functions */
 int DECL_EFFECTIVE_INIT_PRIORITY (scalar_t__) ; 
 int /*<<< orphan*/  EQ_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TREE_PURPOSE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_HAS_TRIVIAL_DESTRUCTOR (int /*<<< orphan*/ ) ; 
 scalar_t__ begin_if_stmt () ; 
 scalar_t__ build_int_cst (int /*<<< orphan*/ ,int) ; 
 scalar_t__ cp_build_binary_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  finish_if_stmt (scalar_t__) ; 
 int /*<<< orphan*/  finish_if_stmt_cond (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  finish_then_clause (scalar_t__) ; 
 TYPE_1__* get_priority_info (int) ; 
 int /*<<< orphan*/  initialize_p_decl ; 
 scalar_t__ integer_one_node ; 
 scalar_t__ integer_zero_node ; 
 int /*<<< orphan*/  one_static_initialization_or_destruction (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  priority_decl ; 

__attribute__((used)) static void
do_static_initialization_or_destruction (tree vars, bool initp)
{
  tree node, init_if_stmt, cond;

  /* Build the outer if-stmt to check for initialization or destruction.  */
  init_if_stmt = begin_if_stmt ();
  cond = initp ? integer_one_node : integer_zero_node;
  cond = cp_build_binary_op (EQ_EXPR,
				  initialize_p_decl,
				  cond);
  finish_if_stmt_cond (cond, init_if_stmt);

  node = vars;
  do {
    tree decl = TREE_VALUE (node);
    tree priority_if_stmt;
    int priority;
    priority_info pi;

    /* If we don't need a destructor, there's nothing to do.  Avoid
       creating a possibly empty if-stmt.  */
    if (!initp && TYPE_HAS_TRIVIAL_DESTRUCTOR (TREE_TYPE (decl)))
      {
	node = TREE_CHAIN (node);
	continue;
      }

    /* Remember that we had an initialization or finalization at this
       priority.  */
    priority = DECL_EFFECTIVE_INIT_PRIORITY (decl);
    pi = get_priority_info (priority);
    if (initp)
      pi->initializations_p = 1;
    else
      pi->destructions_p = 1;

    /* Conditionalize this initialization on being in the right priority
       and being initializing/finalizing appropriately.  */
    priority_if_stmt = begin_if_stmt ();
    cond = cp_build_binary_op (EQ_EXPR,
			       priority_decl,
			       build_int_cst (NULL_TREE, priority));
    finish_if_stmt_cond (cond, priority_if_stmt);

    /* Process initializers with same priority.  */
    for (; node
	   && DECL_EFFECTIVE_INIT_PRIORITY (TREE_VALUE (node)) == priority;
	 node = TREE_CHAIN (node))
      /* Do one initialization or destruction.  */
      one_static_initialization_or_destruction (TREE_VALUE (node),
						TREE_PURPOSE (node), initp);

    /* Finish up the priority if-stmt body.  */
    finish_then_clause (priority_if_stmt);
    finish_if_stmt (priority_if_stmt);

  } while (node);

  /* Finish up the init/destruct if-stmt body.  */
  finish_then_clause (init_if_stmt);
  finish_if_stmt (init_if_stmt);
}