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
struct omp_region {int type; struct omp_region* next; struct omp_region* inner; int /*<<< orphan*/  entry; struct omp_region* outer; } ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 struct omp_region* root_omp_region ; 
 struct omp_region* xcalloc (int,int) ; 

struct omp_region *
new_omp_region (basic_block bb, enum tree_code type, struct omp_region *parent)
{
  struct omp_region *region = xcalloc (1, sizeof (*region));

  region->outer = parent;
  region->entry = bb;
  region->type = type;

  if (parent)
    {
      /* This is a nested region.  Add it to the list of inner
	 regions in PARENT.  */
      region->next = parent->inner;
      parent->inner = region;
    }
  else
    {
      /* This is a toplevel region.  Add it to the list of toplevel
	 regions in ROOT_OMP_REGION.  */
      region->next = root_omp_region;
      root_omp_region = region;
    }

  return region;
}