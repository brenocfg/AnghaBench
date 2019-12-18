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
struct tree_int_map {int /*<<< orphan*/  from; } ;

/* Variables and functions */
 unsigned int htab_hash_pointer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
tree_int_map_hash (const void *item)
{
  return htab_hash_pointer (((const struct tree_int_map *)item)->from);
}