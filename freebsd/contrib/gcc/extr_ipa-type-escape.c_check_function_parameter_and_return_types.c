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
 scalar_t__ DECL_ARGUMENTS (scalar_t__) ; 
 int /*<<< orphan*/  EXPOSED_PARAMETER ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_ARG_TYPES (scalar_t__) ; 
 scalar_t__ get_canon_type (scalar_t__,int,int) ; 
 int /*<<< orphan*/  mark_interesting_type (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ void_type_node ; 

__attribute__((used)) static void 
check_function_parameter_and_return_types (tree fn, bool escapes) 
{
  tree arg;
  
  if (TYPE_ARG_TYPES (TREE_TYPE (fn)))
    {
      for (arg = TYPE_ARG_TYPES (TREE_TYPE (fn));
	   arg && TREE_VALUE (arg) != void_type_node;
	   arg = TREE_CHAIN (arg))
	{
	  tree type = get_canon_type (TREE_VALUE (arg), false, false);
	  if (escapes)
	    mark_interesting_type (type, EXPOSED_PARAMETER);
	}
    }
  else
    {
      /* FIXME - According to Geoff Keating, we should never have to
	 do this; the front ends should always process the arg list
	 from the TYPE_ARG_LIST. However, Geoff is wrong, this code
	 does seem to be live.  */

      for (arg = DECL_ARGUMENTS (fn); arg; arg = TREE_CHAIN (arg))
	{
	  tree type = get_canon_type (TREE_TYPE (arg), false, false);
	  if (escapes)
	    mark_interesting_type (type, EXPOSED_PARAMETER);
	}
    }
  if (escapes)
    {
      tree type = get_canon_type (TREE_TYPE (TREE_TYPE (fn)), false, false);
      mark_interesting_type (type, EXPOSED_PARAMETER); 
    }
}