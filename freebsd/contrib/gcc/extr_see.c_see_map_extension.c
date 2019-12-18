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
struct see_pre_extension_expr {size_t bitmap_index; } ;

/* Variables and functions */

__attribute__((used)) static int
see_map_extension (void **slot, void *b)
{
  struct see_pre_extension_expr *expr = *slot;
  struct see_pre_extension_expr **index_map =
    (struct see_pre_extension_expr **) b;

  index_map[expr->bitmap_index] = expr;

  return 1;
}