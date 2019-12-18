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
struct cxx_int_tree_map {unsigned int uid; } ;

/* Variables and functions */

unsigned int
cxx_int_tree_map_hash (const void *item)
{
  return ((const struct cxx_int_tree_map *)item)->uid;
}