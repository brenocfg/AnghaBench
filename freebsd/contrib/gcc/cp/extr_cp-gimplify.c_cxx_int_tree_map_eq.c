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
struct cxx_int_tree_map {scalar_t__ uid; } ;

/* Variables and functions */

int
cxx_int_tree_map_eq (const void *va, const void *vb)
{
  const struct cxx_int_tree_map *a = (const struct cxx_int_tree_map *) va;
  const struct cxx_int_tree_map *b = (const struct cxx_int_tree_map *) vb;
  return (a->uid == b->uid);
}