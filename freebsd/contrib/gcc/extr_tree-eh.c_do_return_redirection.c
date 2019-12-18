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
typedef  void* tree ;
struct goto_queue_node {int /*<<< orphan*/  repl_stmt; void* stmt; void* cont_stmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GOTO_EXPR ; 
#define  MODIFY_EXPR 129 
#define  RESULT_DECL 128 
 int /*<<< orphan*/  RETURN_EXPR ; 
 int TREE_CODE (void*) ; 
 void* TREE_OPERAND (void*,int) ; 
 int /*<<< orphan*/  TREE_TYPE (void*) ; 
 int /*<<< orphan*/  aggregate_value_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_to_statement_list (void*,int /*<<< orphan*/ *) ; 
 void* build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 void* build2 (int const,int /*<<< orphan*/ ,void*,void*) ; 
 void* create_tmp_var (int /*<<< orphan*/ ,char*) ; 
 void* current_function_decl ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static void
do_return_redirection (struct goto_queue_node *q, tree finlab, tree mod,
		       tree *return_value_p)
{
  tree ret_expr = TREE_OPERAND (q->stmt, 0);
  tree x;

  if (ret_expr)
    {
      /* The nasty part about redirecting the return value is that the
	 return value itself is to be computed before the FINALLY block
	 is executed.  e.g.

		int x;
		int foo (void)
		{
		  x = 0;
		  try {
		    return x;
		  } finally {
		    x++;
		  }
		}

	  should return 0, not 1.  Arrange for this to happen by copying
	  computed the return value into a local temporary.  This also
	  allows us to redirect multiple return statements through the
	  same destination block; whether this is a net win or not really
	  depends, I guess, but it does make generation of the switch in
	  lower_try_finally_switch easier.  */

      switch (TREE_CODE (ret_expr))
	{
	case RESULT_DECL:
	  if (!*return_value_p)
	    *return_value_p = ret_expr;
	  else
	    gcc_assert (*return_value_p == ret_expr);
	  q->cont_stmt = q->stmt;
	  break;

	case MODIFY_EXPR:
	  {
	    tree result = TREE_OPERAND (ret_expr, 0);
	    tree new, old = TREE_OPERAND (ret_expr, 1);

	    if (!*return_value_p)
	      {
		if (aggregate_value_p (TREE_TYPE (result),
				      TREE_TYPE (current_function_decl)))
		  /* If this function returns in memory, copy the argument
		    into the return slot now.  Otherwise, we might need to
		    worry about magic return semantics, so we need to use a
		    temporary to hold the value until we're actually ready
		    to return.  */
		  new = result;
		else
		  new = create_tmp_var (TREE_TYPE (old), "rettmp");
		*return_value_p = new;
	      }
	    else
	      new = *return_value_p;

	    x = build2 (MODIFY_EXPR, TREE_TYPE (new), new, old);
	    append_to_statement_list (x, &q->repl_stmt);

	    if (new == result)
	      x = result;
	    else
	      x = build2 (MODIFY_EXPR, TREE_TYPE (result), result, new);
	    q->cont_stmt = build1 (RETURN_EXPR, void_type_node, x);
	  }

	default:
	  gcc_unreachable ();
	}
    }
  else
    {
      /* If we don't return a value, all return statements are the same.  */
      q->cont_stmt = q->stmt;
    }

  if (mod)
    append_to_statement_list (mod, &q->repl_stmt);

  x = build1 (GOTO_EXPR, void_type_node, finlab);
  append_to_statement_list (x, &q->repl_stmt);
}