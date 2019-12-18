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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 scalar_t__ DECL_CONV_FN_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_CONV_FN_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_DESTRUCTOR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_ARG_TYPES (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_QUALS (int /*<<< orphan*/ ) ; 
 scalar_t__ compparms (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ same_type_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ special_function_p (int /*<<< orphan*/ ) ; 

int
same_signature_p (tree fndecl, tree base_fndecl)
{
  /* One destructor overrides another if they are the same kind of
     destructor.  */
  if (DECL_DESTRUCTOR_P (base_fndecl) && DECL_DESTRUCTOR_P (fndecl)
      && special_function_p (base_fndecl) == special_function_p (fndecl))
    return 1;
  /* But a non-destructor never overrides a destructor, nor vice
     versa, nor do different kinds of destructors override
     one-another.  For example, a complete object destructor does not
     override a deleting destructor.  */
  if (DECL_DESTRUCTOR_P (base_fndecl) || DECL_DESTRUCTOR_P (fndecl))
    return 0;

  if (DECL_NAME (fndecl) == DECL_NAME (base_fndecl)
      || (DECL_CONV_FN_P (fndecl)
	  && DECL_CONV_FN_P (base_fndecl)
	  && same_type_p (DECL_CONV_FN_TYPE (fndecl),
			  DECL_CONV_FN_TYPE (base_fndecl))))
    {
      tree types, base_types;
      types = TYPE_ARG_TYPES (TREE_TYPE (fndecl));
      base_types = TYPE_ARG_TYPES (TREE_TYPE (base_fndecl));
      if ((TYPE_QUALS (TREE_TYPE (TREE_VALUE (base_types)))
	   == TYPE_QUALS (TREE_TYPE (TREE_VALUE (types))))
	  && compparms (TREE_CHAIN (base_types), TREE_CHAIN (types)))
	return 1;
    }
  return 0;
}