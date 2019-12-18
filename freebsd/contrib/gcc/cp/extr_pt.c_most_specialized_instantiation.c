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
typedef  scalar_t__ tree ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_TEMPLATE_RESULT (int /*<<< orphan*/ ) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ get_bindings (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  processing_template_decl ; 

tree
most_specialized_instantiation (tree templates)
{
  tree fn, champ;

  ++processing_template_decl;

  champ = templates;
  for (fn = TREE_CHAIN (templates); fn; fn = TREE_CHAIN (fn))
    {
      int fate = 0;

      if (get_bindings (TREE_VALUE (champ),
			DECL_TEMPLATE_RESULT (TREE_VALUE (fn)),
			NULL_TREE, /*check_ret=*/false))
	fate--;

      if (get_bindings (TREE_VALUE (fn),
			DECL_TEMPLATE_RESULT (TREE_VALUE (champ)),
			NULL_TREE, /*check_ret=*/false))
	fate++;

      if (fate == -1)
	champ = fn;
      else if (!fate)
	{
	  /* Equally specialized, move to next function.  If there
	     is no next function, nothing's most specialized.  */
	  fn = TREE_CHAIN (fn);
	  champ = fn;
	  if (!fn)
	    break;
	}
    }

  if (champ)
    /* Now verify that champ is better than everything earlier in the
       instantiation list.  */
    for (fn = templates; fn != champ; fn = TREE_CHAIN (fn))
      if (get_bindings (TREE_VALUE (champ),
			DECL_TEMPLATE_RESULT (TREE_VALUE (fn)),
			NULL_TREE, /*check_ret=*/false)
	  || !get_bindings (TREE_VALUE (fn),
			    DECL_TEMPLATE_RESULT (TREE_VALUE (champ)),
			    NULL_TREE, /*check_ret=*/false))
	{
	  champ = NULL_TREE;
	  break;
	}

  processing_template_decl--;

  if (!champ)
    return error_mark_node;

  return champ;
}