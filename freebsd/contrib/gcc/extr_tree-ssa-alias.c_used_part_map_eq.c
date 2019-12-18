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
struct used_part_map {scalar_t__ uid; } ;

/* Variables and functions */

__attribute__((used)) static int
used_part_map_eq (const void *va, const void *vb)
{
  const struct used_part_map *a = (const struct used_part_map *) va;
  const struct used_part_map *b = (const struct used_part_map *) vb;
  return (a->uid == b->uid);
}