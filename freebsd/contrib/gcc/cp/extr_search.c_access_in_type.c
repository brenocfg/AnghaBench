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
typedef  int /*<<< orphan*/  access_kind ;

/* Variables and functions */
 int /*<<< orphan*/  BINFO_ACCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_BINFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dfs_access_in_type ; 
 int /*<<< orphan*/  dfs_walk_once (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static access_kind
access_in_type (tree type, tree decl)
{
  tree binfo = TYPE_BINFO (type);

  /* We must take into account

       [class.paths]

       If a name can be reached by several paths through a multiple
       inheritance graph, the access is that of the path that gives
       most access.

    The algorithm we use is to make a post-order depth-first traversal
    of the base-class hierarchy.  As we come up the tree, we annotate
    each node with the most lenient access.  */
  dfs_walk_once (binfo, NULL, dfs_access_in_type, decl);

  return BINFO_ACCESS (binfo);
}