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
struct lookup_base_data_s {scalar_t__ binfo; int via_virtual; int ambiguous; int /*<<< orphan*/  t; scalar_t__ want_any; int /*<<< orphan*/  repeated_base; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BINFO_TYPE (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ SAME_BINFO_TYPE_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ binfo_via_virtual (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ dfs_skip_bases ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

__attribute__((used)) static tree
dfs_lookup_base (tree binfo, void *data_)
{
  struct lookup_base_data_s *data = (struct lookup_base_data_s *) data_;

  if (SAME_BINFO_TYPE_P (BINFO_TYPE (binfo), data->base))
    {
      if (!data->binfo)
	{
	  data->binfo = binfo;
	  data->via_virtual
	    = binfo_via_virtual (data->binfo, data->t) != NULL_TREE;

	  if (!data->repeated_base)
	    /* If there are no repeated bases, we can stop now.  */
	    return binfo;

	  if (data->want_any && !data->via_virtual)
	    /* If this is a non-virtual base, then we can't do
	       better.  */
	    return binfo;

	  return dfs_skip_bases;
	}
      else
	{
	  gcc_assert (binfo != data->binfo);

	  /* We've found more than one matching binfo.  */
	  if (!data->want_any)
	    {
	      /* This is immediately ambiguous.  */
	      data->binfo = NULL_TREE;
	      data->ambiguous = true;
	      return error_mark_node;
	    }

	  /* Prefer one via a non-virtual path.  */
	  if (!binfo_via_virtual (binfo, data->t))
	    {
	      data->binfo = binfo;
	      data->via_virtual = false;
	      return binfo;
	    }

	  /* There must be repeated bases, otherwise we'd have stopped
	     on the first base we found.  */
	  return dfs_skip_bases;
	}
    }

  return NULL_TREE;
}