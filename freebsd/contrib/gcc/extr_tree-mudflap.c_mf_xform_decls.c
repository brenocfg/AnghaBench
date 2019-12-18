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
struct mf_xform_decls_data {int /*<<< orphan*/  param_decls; } ;

/* Variables and functions */
 int /*<<< orphan*/  mx_xfn_xform_decls ; 
 int /*<<< orphan*/  walk_tree_without_duplicates (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mf_xform_decls_data*) ; 

__attribute__((used)) static void
mf_xform_decls (tree fnbody, tree fnparams)
{
  struct mf_xform_decls_data d;
  d.param_decls = fnparams;
  walk_tree_without_duplicates (&fnbody, mx_xfn_xform_decls, &d);
}