#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ vbase; scalar_t__ binfo; int /*<<< orphan*/  rtti_binfo; scalar_t__ ctor_vtbl_p; } ;
typedef  TYPE_1__ vtbl_init_data ;
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ BINFO_INHERITANCE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  BINFO_TYPE (scalar_t__) ; 
 scalar_t__ BINFO_VIRTUALS (scalar_t__) ; 
 scalar_t__ BINFO_VIRTUAL_P (scalar_t__) ; 
 scalar_t__ BV_FN (scalar_t__) ; 
 int /*<<< orphan*/  DECL_CONTEXT (scalar_t__) ; 
 scalar_t__ DECL_VINDEX (scalar_t__) ; 
 int /*<<< orphan*/  SAME_BINFO_TYPE_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TYPE_BINFO (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_METHODS (int /*<<< orphan*/ ) ; 
 scalar_t__ abi_version_at_least (int) ; 
 int /*<<< orphan*/  add_vcall_offset (scalar_t__,scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ get_primary_binfo (scalar_t__) ; 
 scalar_t__ original_binfo (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_vcall_offset_vtbl_entries_1 (tree binfo, vtbl_init_data* vid)
{
  /* Make entries for the rest of the virtuals.  */
  if (abi_version_at_least (2))
    {
      tree orig_fn;

      /* The ABI requires that the methods be processed in declaration
	 order.  G++ 3.2 used the order in the vtable.  */
      for (orig_fn = TYPE_METHODS (BINFO_TYPE (binfo));
	   orig_fn;
	   orig_fn = TREE_CHAIN (orig_fn))
	if (DECL_VINDEX (orig_fn))
	  add_vcall_offset (orig_fn, binfo, vid);
    }
  else
    {
      tree derived_virtuals;
      tree base_virtuals;
      tree orig_virtuals;
      /* If BINFO is a primary base, the most derived class which has
	 BINFO as a primary base; otherwise, just BINFO.  */
      tree non_primary_binfo;

      /* We might be a primary base class.  Go up the inheritance hierarchy
	 until we find the most derived class of which we are a primary base:
	 it is the BINFO_VIRTUALS there that we need to consider.  */
      non_primary_binfo = binfo;
      while (BINFO_INHERITANCE_CHAIN (non_primary_binfo))
	{
	  tree b;

	  /* If we have reached a virtual base, then it must be vid->vbase,
	     because we ignore other virtual bases in
	     add_vcall_offset_vtbl_entries_r.  In turn, it must be a primary
	     base (possibly multi-level) of vid->binfo, or we wouldn't
	     have called build_vcall_and_vbase_vtbl_entries for it.  But it
	     might be a lost primary, so just skip down to vid->binfo.  */
	  if (BINFO_VIRTUAL_P (non_primary_binfo))
	    {
	      gcc_assert (non_primary_binfo == vid->vbase);
	      non_primary_binfo = vid->binfo;
	      break;
	    }

	  b = BINFO_INHERITANCE_CHAIN (non_primary_binfo);
	  if (get_primary_binfo (b) != non_primary_binfo)
	    break;
	  non_primary_binfo = b;
	}

      if (vid->ctor_vtbl_p)
	/* For a ctor vtable we need the equivalent binfo within the hierarchy
	   where rtti_binfo is the most derived type.  */
	non_primary_binfo
	  = original_binfo (non_primary_binfo, vid->rtti_binfo);

      for (base_virtuals = BINFO_VIRTUALS (binfo),
	     derived_virtuals = BINFO_VIRTUALS (non_primary_binfo),
	     orig_virtuals = BINFO_VIRTUALS (TYPE_BINFO (BINFO_TYPE (binfo)));
	   base_virtuals;
	   base_virtuals = TREE_CHAIN (base_virtuals),
	     derived_virtuals = TREE_CHAIN (derived_virtuals),
	     orig_virtuals = TREE_CHAIN (orig_virtuals))
	{
	  tree orig_fn;

	  /* Find the declaration that originally caused this function to
	     be present in BINFO_TYPE (binfo).  */
	  orig_fn = BV_FN (orig_virtuals);

	  /* When processing BINFO, we only want to generate vcall slots for
	     function slots introduced in BINFO.  So don't try to generate
	     one if the function isn't even defined in BINFO.  */
	  if (!SAME_BINFO_TYPE_P (BINFO_TYPE (binfo), DECL_CONTEXT (orig_fn)))
	    continue;

	  add_vcall_offset (orig_fn, binfo, vid);
	}
    }
}