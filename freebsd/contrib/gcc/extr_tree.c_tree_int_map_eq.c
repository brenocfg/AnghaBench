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
struct tree_int_map {scalar_t__ from; } ;

/* Variables and functions */

__attribute__((used)) static int
tree_int_map_eq (const void *va, const void *vb)
{
  const struct tree_int_map  *a = va, *b = vb;
  return (a->from == b->from);
}