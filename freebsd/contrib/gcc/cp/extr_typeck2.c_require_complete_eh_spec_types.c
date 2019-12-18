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
typedef  char* tree ;

/* Variables and functions */
 int /*<<< orphan*/  COMPLETE_TYPE_P (char*) ; 
 scalar_t__ DECL_ARTIFICIAL (char*) ; 
 char* TREE_CHAIN (char*) ; 
 char* TREE_VALUE (char*) ; 
 char* TYPE_RAISES_EXCEPTIONS (char*) ; 
 int /*<<< orphan*/  error (char*,char*,...) ; 

void
require_complete_eh_spec_types (tree fntype, tree decl)
{
  tree raises;
  /* Don't complain about calls to op new.  */
  if (decl && DECL_ARTIFICIAL (decl))
    return;
  for (raises = TYPE_RAISES_EXCEPTIONS (fntype); raises;
       raises = TREE_CHAIN (raises))
    {
      tree type = TREE_VALUE (raises);
      if (type && !COMPLETE_TYPE_P (type))
	{
	  if (decl)
	    error
	      ("call to function %qD which throws incomplete type %q#T",
	       decl, type);
	  else
	    error ("call to function which throws incomplete type %q#T",
		   decl);
	}
    }
}