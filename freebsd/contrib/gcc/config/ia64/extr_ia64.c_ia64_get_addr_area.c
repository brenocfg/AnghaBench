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
typedef  int /*<<< orphan*/  ia64_addr_area ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_AREA_NORMAL ; 
 int /*<<< orphan*/  ADDR_AREA_SMALL ; 
 int /*<<< orphan*/  DECL_ATTRIBUTES (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  init_idents () ; 
 scalar_t__ lookup_attribute (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ small_ident1 ; 
 scalar_t__ small_ident2 ; 

__attribute__((used)) static ia64_addr_area
ia64_get_addr_area (tree decl)
{
  tree model_attr;

  model_attr = lookup_attribute ("model", DECL_ATTRIBUTES (decl));
  if (model_attr)
    {
      tree id;

      init_idents ();
      id = TREE_VALUE (TREE_VALUE (model_attr));
      if (id == small_ident1 || id == small_ident2)
	return ADDR_AREA_SMALL;
    }
  return ADDR_AREA_NORMAL;
}