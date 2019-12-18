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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  splay_tree ;
typedef  TYPE_1__* record_layout_info ;
struct TYPE_4__ {scalar_t__ t; } ;

/* Variables and functions */
 scalar_t__ BINFO_BASE_BINFO (int /*<<< orphan*/ ,int) ; 
 int BINFO_N_BASE_BINFOS (int /*<<< orphan*/ ) ; 
 scalar_t__ BINFO_VIRTUAL_P (scalar_t__) ; 
 scalar_t__ CLASSTYPE_HAS_PRIMARY_BASE_P (scalar_t__) ; 
 scalar_t__ CLASSTYPE_PRIMARY_BINFO (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_BINFO (scalar_t__) ; 
 scalar_t__* build_base_field (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void
build_base_fields (record_layout_info rli,
		   splay_tree offsets, tree *next_field)
{
  /* Chain to hold all the new FIELD_DECLs which stand in for base class
     subobjects.  */
  tree t = rli->t;
  int n_baseclasses = BINFO_N_BASE_BINFOS (TYPE_BINFO (t));
  int i;

  /* The primary base class is always allocated first.  */
  if (CLASSTYPE_HAS_PRIMARY_BASE_P (t))
    next_field = build_base_field (rli, CLASSTYPE_PRIMARY_BINFO (t),
				   offsets, next_field);

  /* Now allocate the rest of the bases.  */
  for (i = 0; i < n_baseclasses; ++i)
    {
      tree base_binfo;

      base_binfo = BINFO_BASE_BINFO (TYPE_BINFO (t), i);

      /* The primary base was already allocated above, so we don't
	 need to allocate it again here.  */
      if (base_binfo == CLASSTYPE_PRIMARY_BINFO (t))
	continue;

      /* Virtual bases are added at the end (a primary virtual base
	 will have already been added).  */
      if (BINFO_VIRTUAL_P (base_binfo))
	continue;

      next_field = build_base_field (rli, base_binfo,
				     offsets, next_field);
    }
}