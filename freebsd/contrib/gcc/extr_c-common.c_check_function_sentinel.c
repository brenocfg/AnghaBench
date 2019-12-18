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
 int /*<<< orphan*/  OPT_Wformat ; 
 int /*<<< orphan*/  POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 unsigned int TREE_INT_CST_LOW (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  integer_zerop (scalar_t__) ; 
 scalar_t__ lookup_attribute (char*,scalar_t__) ; 
 scalar_t__ null_node ; 
 scalar_t__ warn_strict_null_sentinel ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
check_function_sentinel (tree attrs, tree params, tree typelist)
{
  tree attr = lookup_attribute ("sentinel", attrs);

  if (attr)
    {
      /* Skip over the named arguments.  */
      while (typelist && params)
      {
	typelist = TREE_CHAIN (typelist);
	params = TREE_CHAIN (params);
      }

      if (typelist || !params)
	warning (OPT_Wformat,
		 "not enough variable arguments to fit a sentinel");
      else
	{
	  tree sentinel, end;
	  unsigned pos = 0;

	  if (TREE_VALUE (attr))
	    {
	      tree p = TREE_VALUE (TREE_VALUE (attr));
	      pos = TREE_INT_CST_LOW (p);
	    }

	  sentinel = end = params;

	  /* Advance `end' ahead of `sentinel' by `pos' positions.  */
	  while (pos > 0 && TREE_CHAIN (end))
	    {
	      pos--;
	      end = TREE_CHAIN (end);
	    }
	  if (pos > 0)
	    {
	      warning (OPT_Wformat,
		       "not enough variable arguments to fit a sentinel");
	      return;
	    }

	  /* Now advance both until we find the last parameter.  */
	  while (TREE_CHAIN (end))
	    {
	      end = TREE_CHAIN (end);
	      sentinel = TREE_CHAIN (sentinel);
	    }

	  /* Validate the sentinel.  */
	  if ((!POINTER_TYPE_P (TREE_TYPE (TREE_VALUE (sentinel)))
	       || !integer_zerop (TREE_VALUE (sentinel)))
	      /* Although __null (in C++) is only an integer we allow it
		 nevertheless, as we are guaranteed that it's exactly
		 as wide as a pointer, and we don't want to force
		 users to cast the NULL they have written there.
		 We warn with -Wstrict-null-sentinel, though.  */
	      && (warn_strict_null_sentinel
		  || null_node != TREE_VALUE (sentinel)))
	    warning (OPT_Wformat, "missing sentinel in function call");
	}
    }
}