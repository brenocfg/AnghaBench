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
 scalar_t__ DECL_CONTEXT (scalar_t__) ; 
 scalar_t__ IDENTIFIER_LABEL_VALUE (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  POP_TIMEVAR_AND_RETURN (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TV_NAME_LOOKUP ; 
 scalar_t__ current_function_decl ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 scalar_t__ make_label_decl (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 

tree
lookup_label (tree id)
{
  tree decl;

  timevar_push (TV_NAME_LOOKUP);
  /* You can't use labels at global scope.  */
  if (current_function_decl == NULL_TREE)
    {
      error ("label %qE referenced outside of any function", id);
      POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, NULL_TREE);
    }

  /* See if we've already got this label.  */
  decl = IDENTIFIER_LABEL_VALUE (id);
  if (decl != NULL_TREE && DECL_CONTEXT (decl) == current_function_decl)
    POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, decl);

  decl = make_label_decl (id, /*local_p=*/0);
  POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, decl);
}