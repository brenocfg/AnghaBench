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
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ VOID_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alias_sets_conflict_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_alias_set (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
nonstandard_alias_types_p (tree type1, tree type2)
{
  HOST_WIDE_INT set1;
  HOST_WIDE_INT set2;

  if (VOID_TYPE_P (type1) || VOID_TYPE_P (type2))
    return false;

  set1 = get_alias_set (type1);
  set2 = get_alias_set (type2);
  return !alias_sets_conflict_p (set1, set2);
}