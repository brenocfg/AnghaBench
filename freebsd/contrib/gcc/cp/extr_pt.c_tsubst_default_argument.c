#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* tree ;
struct TYPE_2__ {void* x_current_class_ref; void* x_current_class_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_TI_ARGS (void*) ; 
 void* NULL_TREE ; 
 scalar_t__ cfun ; 
 void* check_default_argument (void*,void*) ; 
 TYPE_1__* cp_function_chain ; 
 void* current_class_ptr ; 
 void* current_class_ref ; 
 int /*<<< orphan*/  dk_no_deferred ; 
 int /*<<< orphan*/  function_depth ; 
 int /*<<< orphan*/  pop_access_scope (void*) ; 
 int /*<<< orphan*/  pop_deferring_access_checks () ; 
 int /*<<< orphan*/  push_access_scope (void*) ; 
 int /*<<< orphan*/  push_deferring_access_checks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tf_warning_or_error ; 
 void* tsubst_expr (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

tree
tsubst_default_argument (tree fn, tree type, tree arg)
{
  tree saved_class_ptr = NULL_TREE;
  tree saved_class_ref = NULL_TREE;

  /* This default argument came from a template.  Instantiate the
     default argument here, not in tsubst.  In the case of
     something like:

       template <class T>
       struct S {
	 static T t();
	 void f(T = t());
       };

     we must be careful to do name lookup in the scope of S<T>,
     rather than in the current class.  */
  push_access_scope (fn);
  /* The "this" pointer is not valid in a default argument.  */
  if (cfun)
    {
      saved_class_ptr = current_class_ptr;
      cp_function_chain->x_current_class_ptr = NULL_TREE;
      saved_class_ref = current_class_ref;
      cp_function_chain->x_current_class_ref = NULL_TREE;
    }

  push_deferring_access_checks(dk_no_deferred);
  /* The default argument expression may cause implicitly defined
     member functions to be synthesized, which will result in garbage
     collection.  We must treat this situation as if we were within
     the body of function so as to avoid collecting live data on the
     stack.  */
  ++function_depth;
  arg = tsubst_expr (arg, DECL_TI_ARGS (fn),
		     tf_warning_or_error, NULL_TREE,
		     /*integral_constant_expression_p=*/false);
  --function_depth;
  pop_deferring_access_checks();

  /* Restore the "this" pointer.  */
  if (cfun)
    {
      cp_function_chain->x_current_class_ptr = saved_class_ptr;
      cp_function_chain->x_current_class_ref = saved_class_ref;
    }

  pop_access_scope (fn);

  /* Make sure the default argument is reasonable.  */
  arg = check_default_argument (type, arg);

  return arg;
}