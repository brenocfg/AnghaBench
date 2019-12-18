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
typedef  scalar_t__ bitmap_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_insert_into_set (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bitmap_value_insert_into_set (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vn_add (scalar_t__,scalar_t__) ; 
 scalar_t__ vn_lookup_or_add (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void
add_to_sets (tree var, tree expr, tree stmt, bitmap_set_t s1,
	     bitmap_set_t s2)
{
  tree val = vn_lookup_or_add (expr, stmt);

  /* VAR and EXPR may be the same when processing statements for which
     we are not computing value numbers (e.g., non-assignments, or
     statements that make aliased stores).  In those cases, we are
     only interested in making VAR available as its own value.  */
  if (var != expr)
    vn_add (var, val);

  if (s1)
    bitmap_insert_into_set (s1, var);
  bitmap_value_insert_into_set (s2, var);
}