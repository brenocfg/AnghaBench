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
 int GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ IDENTIFIER_NODE ; 
 int /*<<< orphan*/  KEEP_AGGREGATE_RETURN_POINTER ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  TARGET_64BIT ; 
 scalar_t__ TARGET_RTD ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_VALUE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_ARG_TYPES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_ATTRIBUTES (int /*<<< orphan*/ ) ; 
 scalar_t__ aggregate_value_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ix86_function_regparm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lookup_attribute (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_last (scalar_t__) ; 
 scalar_t__ void_type_node ; 

int
ix86_return_pops_args (tree fundecl, tree funtype, int size)
{
  int rtd = TARGET_RTD && (!fundecl || TREE_CODE (fundecl) != IDENTIFIER_NODE);

  /* Cdecl functions override -mrtd, and never pop the stack.  */
  if (! lookup_attribute ("cdecl", TYPE_ATTRIBUTES (funtype))) {

    /* Stdcall and fastcall functions will pop the stack if not
       variable args.  */
    if (lookup_attribute ("stdcall", TYPE_ATTRIBUTES (funtype))
        || lookup_attribute ("fastcall", TYPE_ATTRIBUTES (funtype)))
      rtd = 1;

    if (rtd
        && (TYPE_ARG_TYPES (funtype) == NULL_TREE
	    || (TREE_VALUE (tree_last (TYPE_ARG_TYPES (funtype)))
		== void_type_node)))
      return size;
  }

  /* Lose any fake structure return argument if it is passed on the stack.  */
  if (aggregate_value_p (TREE_TYPE (funtype), fundecl)
      && !TARGET_64BIT
      && !KEEP_AGGREGATE_RETURN_POINTER)
    {
      int nregs = ix86_function_regparm (funtype, fundecl);

      if (!nregs)
	return GET_MODE_SIZE (Pmode);
    }

  return 0;
}