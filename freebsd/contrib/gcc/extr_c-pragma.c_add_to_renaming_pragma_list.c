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
 int /*<<< orphan*/  OPT_Wpragmas ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  pending_redefine_extname ; 
 scalar_t__ purpose_member (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_cons (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

void
add_to_renaming_pragma_list (tree oldname, tree newname)
{
  tree previous = purpose_member (oldname, pending_redefine_extname);
  if (previous)
    {
      if (TREE_VALUE (previous) != newname)
	warning (OPT_Wpragmas, "#pragma redefine_extname ignored due to "
		 "conflict with previous #pragma redefine_extname");
      return;
    }

  pending_redefine_extname
    = tree_cons (oldname, newname, pending_redefine_extname);
}