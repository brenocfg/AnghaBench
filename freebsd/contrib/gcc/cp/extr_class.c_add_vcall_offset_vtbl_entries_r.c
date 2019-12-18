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
struct TYPE_4__ {scalar_t__ vbase; } ;
typedef  TYPE_1__ vtbl_init_data ;
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ BINFO_BASE_ITERATE (scalar_t__,int,scalar_t__) ; 
 scalar_t__ BINFO_VIRTUAL_P (scalar_t__) ; 
 int /*<<< orphan*/  add_vcall_offset_vtbl_entries_1 (scalar_t__,TYPE_1__*) ; 
 scalar_t__ get_primary_binfo (scalar_t__) ; 

__attribute__((used)) static void
add_vcall_offset_vtbl_entries_r (tree binfo, vtbl_init_data* vid)
{
  int i;
  tree primary_binfo;
  tree base_binfo;

  /* Don't walk into virtual bases -- except, of course, for the
     virtual base for which we are building vcall offsets.  Any
     primary virtual base will have already had its offsets generated
     through the recursion in build_vcall_and_vbase_vtbl_entries.  */
  if (BINFO_VIRTUAL_P (binfo) && vid->vbase != binfo)
    return;

  /* If BINFO has a primary base, process it first.  */
  primary_binfo = get_primary_binfo (binfo);
  if (primary_binfo)
    add_vcall_offset_vtbl_entries_r (primary_binfo, vid);

  /* Add BINFO itself to the list.  */
  add_vcall_offset_vtbl_entries_1 (binfo, vid);

  /* Scan the non-primary bases of BINFO.  */
  for (i = 0; BINFO_BASE_ITERATE (binfo, i, base_binfo); ++i)
    if (base_binfo != primary_binfo)
      add_vcall_offset_vtbl_entries_r (base_binfo, vid);
}