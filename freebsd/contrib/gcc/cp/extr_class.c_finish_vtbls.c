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
 int /*<<< orphan*/  BINFO_VIRTUAL_P (scalar_t__) ; 
 scalar_t__ BINFO_VTABLE (scalar_t__) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_BINFO (scalar_t__) ; 
 int /*<<< orphan*/  accumulate_vtbl_inits (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ build_tree_list (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initialize_vtable (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
finish_vtbls (tree t)
{
  tree list;
  tree vbase;

  /* We lay out the primary and secondary vtables in one contiguous
     vtable.  The primary vtable is first, followed by the non-virtual
     secondary vtables in inheritance graph order.  */
  list = build_tree_list (BINFO_VTABLE (TYPE_BINFO (t)), NULL_TREE);
  accumulate_vtbl_inits (TYPE_BINFO (t), TYPE_BINFO (t),
			 TYPE_BINFO (t), t, list);

  /* Then come the virtual bases, also in inheritance graph order.  */
  for (vbase = TYPE_BINFO (t); vbase; vbase = TREE_CHAIN (vbase))
    {
      if (!BINFO_VIRTUAL_P (vbase))
	continue;
      accumulate_vtbl_inits (vbase, vbase, TYPE_BINFO (t), t, list);
    }

  if (BINFO_VTABLE (TYPE_BINFO (t)))
    initialize_vtable (TYPE_BINFO (t), TREE_VALUE (list));
}