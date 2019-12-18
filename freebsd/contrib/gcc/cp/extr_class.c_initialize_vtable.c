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
 int /*<<< orphan*/  BINFO_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_vtable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_vtbl_decl_for_binfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initialize_artificial_var (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layout_vtable_decl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_length (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
initialize_vtable (tree binfo, tree inits)
{
  tree decl;

  layout_vtable_decl (binfo, list_length (inits));
  decl = get_vtbl_decl_for_binfo (binfo);
  initialize_artificial_var (decl, inits);
  dump_vtable (BINFO_TYPE (binfo), binfo, decl);
}