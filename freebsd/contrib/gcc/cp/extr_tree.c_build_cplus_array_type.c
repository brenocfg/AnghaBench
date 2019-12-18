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
 int TYPE_UNQUALIFIED ; 
 int /*<<< orphan*/  build_cplus_array_type_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_build_qualified_type (int /*<<< orphan*/ ,int) ; 
 int cp_type_quals (int /*<<< orphan*/ ) ; 

tree
build_cplus_array_type (tree elt_type, tree index_type)
{
  tree t;
  int type_quals = cp_type_quals (elt_type);

  if (type_quals != TYPE_UNQUALIFIED)
    elt_type = cp_build_qualified_type (elt_type, TYPE_UNQUALIFIED);

  t = build_cplus_array_type_1 (elt_type, index_type);

  if (type_quals != TYPE_UNQUALIFIED)
    t = cp_build_qualified_type (t, type_quals);

  return t;
}