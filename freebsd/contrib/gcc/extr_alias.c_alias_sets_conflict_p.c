#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  splay_tree_key ;
typedef  TYPE_1__* alias_set_entry ;
struct TYPE_3__ {int /*<<< orphan*/  children; scalar_t__ has_zero_child; } ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 TYPE_1__* get_alias_set_entry (scalar_t__) ; 
 scalar_t__ splay_tree_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
alias_sets_conflict_p (HOST_WIDE_INT set1, HOST_WIDE_INT set2)
{
  alias_set_entry ase;

  /* If have no alias set information for one of the operands, we have
     to assume it can alias anything.  */
  if (set1 == 0 || set2 == 0
      /* If the two alias sets are the same, they may alias.  */
      || set1 == set2)
    return 1;

  /* See if the first alias set is a subset of the second.  */
  ase = get_alias_set_entry (set1);
  if (ase != 0
      && (ase->has_zero_child
	  || splay_tree_lookup (ase->children,
				(splay_tree_key) set2)))
    return 1;

  /* Now do the same, but with the alias sets reversed.  */
  ase = get_alias_set_entry (set2);
  if (ase != 0
      && (ase->has_zero_child
	  || splay_tree_lookup (ase->children,
				(splay_tree_key) set1)))
    return 1;

  /* The two alias sets are distinct and neither one is the
     child of the other.  Therefore, they cannot alias.  */
  return 0;
}