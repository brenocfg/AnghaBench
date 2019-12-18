#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_2__ {scalar_t__ escape_mask; } ;

/* Variables and functions */
 scalar_t__ NO_ESCAPE ; 
 scalar_t__ find_first_artificial_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_otype (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_ssa_base (int /*<<< orphan*/ ) ; 
 int nonstandard_alias_types_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ struct_class_union_p (int /*<<< orphan*/ ) ; 
 scalar_t__ struct_field_tag_p (int /*<<< orphan*/ ) ; 
 TYPE_1__* var_ann (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
nonstandard_alias_p (tree ptr, tree alias, bool ptr_ptr)
{
  /* Find the types to compare.  */
  tree ptr_type = get_otype (ptr, true);
  tree alias_type = get_otype (alias, ptr_ptr);

  /* XXX: for now, say it's OK if the alias escapes.
     Not sure this is needed in general, but otherwise GCC will not
     bootstrap.  */
  if (var_ann (get_ssa_base (alias))->escape_mask != NO_ESCAPE)
      return false;

  /* XXX: don't get into structures for now.  It brings much complication
     and little benefit.  */
  if (struct_class_union_p (ptr_type) || struct_class_union_p (alias_type))
    return false;

  /* XXX: In 4.2.1, field resolution in alias is not as good as in pre-4.3
     This fixes problems found during the backport, where a pointer to the
     first field of a struct appears to be aliased to the whole struct.  */
  if (struct_field_tag_p (alias))
     return false;

  /* If they are both SSA names of artificials, let it go, the warning
     is too confusing.  */
  if (find_first_artificial_name (ptr) && find_first_artificial_name (alias))
    return false;

  /* Compare the types.  */
  return nonstandard_alias_types_p (ptr_type, alias_type);
}