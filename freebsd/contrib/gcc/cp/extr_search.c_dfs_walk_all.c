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
 scalar_t__ BINFO_BASE_ITERATE (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  dfs_skip_bases ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

tree
dfs_walk_all (tree binfo, tree (*pre_fn) (tree, void *),
	      tree (*post_fn) (tree, void *), void *data)
{
  tree rval;
  unsigned ix;
  tree base_binfo;

  /* Call the pre-order walking function.  */
  if (pre_fn)
    {
      rval = pre_fn (binfo, data);
      if (rval)
	{
	  if (rval == dfs_skip_bases)
	    goto skip_bases;
	  return rval;
	}
    }

  /* Find the next child binfo to walk.  */
  for (ix = 0; BINFO_BASE_ITERATE (binfo, ix, base_binfo); ix++)
    {
      rval = dfs_walk_all (base_binfo, pre_fn, post_fn, data);
      if (rval)
	return rval;
    }

 skip_bases:
  /* Call the post-order walking function.  */
  if (post_fn)
    {
      rval = post_fn (binfo, data);
      gcc_assert (rval != dfs_skip_bases);
      return rval;
    }

  return NULL_TREE;
}