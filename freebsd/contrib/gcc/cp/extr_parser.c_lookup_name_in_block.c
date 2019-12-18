#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_4__ {struct TYPE_4__* previous; scalar_t__ declared_in_block; } ;
typedef  TYPE_1__ cxx_binding ;

/* Variables and functions */
 int /*<<< orphan*/  BINDING_VALUE (TYPE_1__*) ; 
 scalar_t__ BLOCK_DECL_BYREF (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_CONTEXT (int /*<<< orphan*/ ) ; 
 TYPE_1__* I_SYMBOL_BINDING (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 scalar_t__ current_function_decl ; 

bool
lookup_name_in_block (tree name, tree *decl)
{
  /* FIXME - Broken, should be found via objc runtime testcases.  */
  /* FIXME - Don't use DECL_CONTEXT on any helpers */
  cxx_binding *b = I_SYMBOL_BINDING (name);
  if (b && b->declared_in_block
      && DECL_CONTEXT (BINDING_VALUE (b)) == current_function_decl)
      return true;

  /* Check for variables only, as we may have parameters, such as
     'self' */
  /* Note that if a copied-in variable (BLOCK_DECL_COPIED) in the
     enclosing block is found, it must be returned as this is
     where the variable in current (nested block) will have to get
     its value. */
  while (b
	  && TREE_CODE (BINDING_VALUE (b)) == VAR_DECL
	  && (BLOCK_DECL_BYREF (BINDING_VALUE (b))))
      b = b->previous;
  if (b)
      *decl = BINDING_VALUE (b);
  return false;
}