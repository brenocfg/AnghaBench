#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * equiv; int /*<<< orphan*/  max; int /*<<< orphan*/  min; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ value_range_t ;
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_FREE (int /*<<< orphan*/ *) ; 
 TYPE_1__* get_value_range (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_value_range (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vrp_bitmap_equal_p (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vrp_operand_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
update_value_range (tree var, value_range_t *new_vr)
{
  value_range_t *old_vr;
  bool is_new;

  /* Update the value range, if necessary.  */
  old_vr = get_value_range (var);
  is_new = old_vr->type != new_vr->type
	   || !vrp_operand_equal_p (old_vr->min, new_vr->min)
	   || !vrp_operand_equal_p (old_vr->max, new_vr->max)
	   || !vrp_bitmap_equal_p (old_vr->equiv, new_vr->equiv);

  if (is_new)
    set_value_range (old_vr, new_vr->type, new_vr->min, new_vr->max,
	             new_vr->equiv);

  BITMAP_FREE (new_vr->equiv);
  new_vr->equiv = NULL;

  return is_new;
}