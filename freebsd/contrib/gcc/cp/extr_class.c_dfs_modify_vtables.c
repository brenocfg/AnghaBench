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
 scalar_t__ BINFO_PRIMARY_P (scalar_t__) ; 
 int /*<<< orphan*/  BINFO_TYPE (scalar_t__) ; 
 scalar_t__ BINFO_VIRTUALS (scalar_t__) ; 
 int /*<<< orphan*/  BINFO_VIRTUAL_P (scalar_t__) ; 
 int /*<<< orphan*/  BV_FN (scalar_t__) ; 
 int /*<<< orphan*/  CLASSTYPE_HAS_PRIMARY_BASE_P (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ SAME_BINFO_TYPE_P (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TYPE_BINFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_CONTAINS_VPTR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ dfs_skip_bases ; 
 int /*<<< orphan*/  make_new_vtable (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  update_vtable_entry_for_fn (scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__*,unsigned int) ; 

__attribute__((used)) static tree
dfs_modify_vtables (tree binfo, void* data)
{
  tree t = (tree) data;
  tree virtuals;
  tree old_virtuals;
  unsigned ix;

  if (!TYPE_CONTAINS_VPTR_P (BINFO_TYPE (binfo)))
    /* A base without a vtable needs no modification, and its bases
       are uninteresting.  */
    return dfs_skip_bases;

  if (SAME_BINFO_TYPE_P (BINFO_TYPE (binfo), t)
      && !CLASSTYPE_HAS_PRIMARY_BASE_P (t))
    /* Don't do the primary vtable, if it's new.  */
    return NULL_TREE;

  if (BINFO_PRIMARY_P (binfo) && !BINFO_VIRTUAL_P (binfo))
    /* There's no need to modify the vtable for a non-virtual primary
       base; we're not going to use that vtable anyhow.  We do still
       need to do this for virtual primary bases, as they could become
       non-primary in a construction vtable.  */
    return NULL_TREE;

  make_new_vtable (t, binfo);

  /* Now, go through each of the virtual functions in the virtual
     function table for BINFO.  Find the final overrider, and update
     the BINFO_VIRTUALS list appropriately.  */
  for (ix = 0, virtuals = BINFO_VIRTUALS (binfo),
	 old_virtuals = BINFO_VIRTUALS (TYPE_BINFO (BINFO_TYPE (binfo)));
       virtuals;
       ix++, virtuals = TREE_CHAIN (virtuals),
	 old_virtuals = TREE_CHAIN (old_virtuals))
    update_vtable_entry_for_fn (t,
				binfo,
				BV_FN (old_virtuals),
				&virtuals, ix);

  return NULL_TREE;
}