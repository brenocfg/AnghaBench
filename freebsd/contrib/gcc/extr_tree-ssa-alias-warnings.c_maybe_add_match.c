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
struct tree_map {scalar_t__ to; } ;
typedef  int /*<<< orphan*/  htab_t ;

/* Variables and functions */
 struct tree_map* htab_find (int /*<<< orphan*/ ,struct tree_map*) ; 

__attribute__((used)) static inline void
maybe_add_match (htab_t ref_map, struct tree_map *key)
{
  struct tree_map *found = htab_find (ref_map, key);

  if (found && !found->to)
    found->to = key->to;
}