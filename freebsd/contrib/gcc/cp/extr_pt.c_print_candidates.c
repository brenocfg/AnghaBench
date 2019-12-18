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
 scalar_t__ NULL_TREE ; 
 char* OVL_CURRENT (scalar_t__) ; 
 scalar_t__ OVL_NEXT (scalar_t__) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  error (char*,char const*,char*) ; 

void
print_candidates (tree fns)
{
  tree fn;

  const char *str = "candidates are:";

  for (fn = fns; fn != NULL_TREE; fn = TREE_CHAIN (fn))
    {
      tree f;

      for (f = TREE_VALUE (fn); f; f = OVL_NEXT (f))
	error ("%s %+#D", str, OVL_CURRENT (f));
      str = "               ";
    }
}