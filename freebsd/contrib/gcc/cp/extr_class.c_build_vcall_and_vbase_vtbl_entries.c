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
typedef  int /*<<< orphan*/  vtbl_init_data ;
typedef  scalar_t__ tree ;

/* Variables and functions */
 int /*<<< orphan*/  build_vbase_offset_vtbl_entries (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  build_vcall_offset_vtbl_entries (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ get_primary_binfo (scalar_t__) ; 

__attribute__((used)) static void
build_vcall_and_vbase_vtbl_entries (tree binfo, vtbl_init_data* vid)
{
  tree b;

  /* If this is a derived class, we must first create entries
     corresponding to the primary base class.  */
  b = get_primary_binfo (binfo);
  if (b)
    build_vcall_and_vbase_vtbl_entries (b, vid);

  /* Add the vbase entries for this base.  */
  build_vbase_offset_vtbl_entries (binfo, vid);
  /* Add the vcall entries for this base.  */
  build_vcall_offset_vtbl_entries (binfo, vid);
}