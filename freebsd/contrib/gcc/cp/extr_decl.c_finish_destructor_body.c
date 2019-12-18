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
typedef  int /*<<< orphan*/  tree ;
struct TYPE_3__ {scalar_t__ (* cdtor_returns_this ) () ;} ;
struct TYPE_4__ {TYPE_1__ cxx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_AND_EXPR ; 
 int /*<<< orphan*/  DECL_ARGUMENTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_RESULT (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_VIRTUAL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELETE_EXPR ; 
 int /*<<< orphan*/  LABEL_EXPR ; 
 int /*<<< orphan*/  MODIFY_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  RETURN_EXPR ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  begin_if_stmt () ; 
 int /*<<< orphan*/  build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_op_delete_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_stmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdtor_label ; 
 int /*<<< orphan*/  current_class_ptr ; 
 int /*<<< orphan*/  current_class_type ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  current_in_charge_parm ; 
 int /*<<< orphan*/  cxx_sizeof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_expr_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_if_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_if_stmt_cond (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_then_clause (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_one_node ; 
 int /*<<< orphan*/  integer_type_node ; 
 scalar_t__ stub1 () ; 
 TYPE_2__ targetm ; 

__attribute__((used)) static void
finish_destructor_body (void)
{
  tree exprstmt;

  /* Any return from a destructor will end up here; that way all base
     and member cleanups will be run when the function returns.  */
  add_stmt (build_stmt (LABEL_EXPR, cdtor_label));

  /* In a virtual destructor, we must call delete.  */
  if (DECL_VIRTUAL_P (current_function_decl))
    {
      tree if_stmt;
      tree virtual_size = cxx_sizeof (current_class_type);

      /* [class.dtor]

      At the point of definition of a virtual destructor (including
      an implicit definition), non-placement operator delete shall
      be looked up in the scope of the destructor's class and if
      found shall be accessible and unambiguous.  */
      exprstmt = build_op_delete_call(DELETE_EXPR, current_class_ptr,
				      virtual_size,
				      /*global_p=*/false,
				      /*placement=*/NULL_TREE,
				      /*alloc_fn=*/NULL_TREE);

      if_stmt = begin_if_stmt ();
      finish_if_stmt_cond (build2 (BIT_AND_EXPR, integer_type_node,
				   current_in_charge_parm,
				   integer_one_node),
			   if_stmt);
      finish_expr_stmt (exprstmt);
      finish_then_clause (if_stmt);
      finish_if_stmt (if_stmt);
    }

  if (targetm.cxx.cdtor_returns_this ())
    {
      tree val;

      val = DECL_ARGUMENTS (current_function_decl);
      val = build2 (MODIFY_EXPR, TREE_TYPE (val),
		    DECL_RESULT (current_function_decl), val);
      /* Return the address of the object.  */
      exprstmt = build_stmt (RETURN_EXPR, val);
      add_stmt (exprstmt);
    }
}