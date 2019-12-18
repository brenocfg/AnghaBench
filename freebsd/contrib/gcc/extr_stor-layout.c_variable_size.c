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
struct TYPE_6__ {scalar_t__ x_dont_save_pending_sizes_p; } ;
struct TYPE_4__ {scalar_t__ (* global_bindings_p ) () ;} ;
struct TYPE_5__ {TYPE_1__ decls; } ;

/* Variables and functions */
 scalar_t__ CONTAINS_PLACEHOLDER_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CONSTANT (int /*<<< orphan*/ ) ; 
 TYPE_3__* cfun ; 
 int /*<<< orphan*/  error (char*) ; 
 TYPE_2__ lang_hooks ; 
 int /*<<< orphan*/  put_pending_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_one_node ; 
 int /*<<< orphan*/  skip_simple_arithmetic (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 () ; 
 scalar_t__ stub2 () ; 

tree
variable_size (tree size)
{
  tree save;

  /* If the language-processor is to take responsibility for variable-sized
     items (e.g., languages which have elaboration procedures like Ada),
     just return SIZE unchanged.  Likewise for self-referential sizes and
     constant sizes.  */
  if (TREE_CONSTANT (size)
      || lang_hooks.decls.global_bindings_p () < 0
      || CONTAINS_PLACEHOLDER_P (size))
    return size;

  size = save_expr (size);

  /* If an array with a variable number of elements is declared, and
     the elements require destruction, we will emit a cleanup for the
     array.  That cleanup is run both on normal exit from the block
     and in the exception-handler for the block.  Normally, when code
     is used in both ordinary code and in an exception handler it is
     `unsaved', i.e., all SAVE_EXPRs are recalculated.  However, we do
     not wish to do that here; the array-size is the same in both
     places.  */
  save = skip_simple_arithmetic (size);

  if (cfun && cfun->x_dont_save_pending_sizes_p)
    /* The front-end doesn't want us to keep a list of the expressions
       that determine sizes for variable size objects.  Trust it.  */
    return size;

  if (lang_hooks.decls.global_bindings_p ())
    {
      if (TREE_CONSTANT (size))
	error ("type size can%'t be explicitly evaluated");
      else
	error ("variable-size type declared outside of any function");

      return size_one_node;
    }

  put_pending_size (save);

  return size;
}