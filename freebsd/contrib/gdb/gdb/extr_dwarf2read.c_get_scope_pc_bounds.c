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
struct dwarf2_cu {int dummy; } ;
struct die_info {int tag; struct die_info* child; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
#define  DW_TAG_namespace 129 
#define  DW_TAG_subprogram 128 
 scalar_t__ dwarf2_get_pc_bounds (struct die_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct die_info* sibling_die (struct die_info*) ; 

__attribute__((used)) static void
get_scope_pc_bounds (struct die_info *die,
		     CORE_ADDR *lowpc, CORE_ADDR *highpc,
		     struct dwarf2_cu *cu)
{
  CORE_ADDR best_low = (CORE_ADDR) -1;
  CORE_ADDR best_high = (CORE_ADDR) 0;
  CORE_ADDR current_low, current_high;

  if (dwarf2_get_pc_bounds (die, &current_low, &current_high, cu))
    {
      best_low = current_low;
      best_high = current_high;
    }
  else
    {
      struct die_info *child = die->child;

      while (child && child->tag)
	{
	  switch (child->tag) {
	  case DW_TAG_subprogram:
	    if (dwarf2_get_pc_bounds (child, &current_low, &current_high, cu))
	      {
		best_low = min (best_low, current_low);
		best_high = max (best_high, current_high);
	      }
	    break;
	  case DW_TAG_namespace:
	    /* FIXME: carlton/2004-01-16: Should we do this for
	       DW_TAG_class_type/DW_TAG_structure_type, too?  I think
	       that current GCC's always emit the DIEs corresponding
	       to definitions of methods of classes as children of a
	       DW_TAG_compile_unit or DW_TAG_namespace (as opposed to
	       the DIEs giving the declarations, which could be
	       anywhere).  But I don't see any reason why the
	       standards says that they have to be there.  */
	    get_scope_pc_bounds (child, &current_low, &current_high, cu);

	    if (current_low != ((CORE_ADDR) -1))
	      {
		best_low = min (best_low, current_low);
		best_high = max (best_high, current_high);
	      }
	    break;
	  default:
	    /* Ignore. */
	    break;
	  }

	  child = sibling_die (child);
	}
    }

  *lowpc = best_low;
  *highpc = best_high;
}