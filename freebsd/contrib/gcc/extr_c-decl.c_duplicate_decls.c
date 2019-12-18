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
typedef  int /*<<< orphan*/ * tree ;
typedef  int TREE_NO_WARNING ;

/* Variables and functions */
 int /*<<< orphan*/  diagnose_mismatched_decls (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  merge_decls (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
duplicate_decls (tree newdecl, tree olddecl)
{
  tree newtype = NULL, oldtype = NULL;

  if (!diagnose_mismatched_decls (newdecl, olddecl, &newtype, &oldtype))
    {
      /* Avoid `unused variable' and other warnings warnings for OLDDECL.  */
      TREE_NO_WARNING (olddecl) = 1;
      return false;
    }

  merge_decls (newdecl, olddecl, newtype, oldtype);
  return true;
}