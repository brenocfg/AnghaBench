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
 scalar_t__ build_variant_type_copy (scalar_t__) ; 
 scalar_t__ get_qualified_type (scalar_t__,int) ; 
 int /*<<< orphan*/  set_type_quals (scalar_t__,int) ; 

tree
build_qualified_type (tree type, int type_quals)
{
  tree t;

  /* See if we already have the appropriate qualified variant.  */
  t = get_qualified_type (type, type_quals);

  /* If not, build it.  */
  if (!t)
    {
      t = build_variant_type_copy (type);
      set_type_quals (t, type_quals);
    }

  return t;
}