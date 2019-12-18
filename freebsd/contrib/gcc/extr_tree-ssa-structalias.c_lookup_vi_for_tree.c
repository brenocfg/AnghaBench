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
typedef  int /*<<< orphan*/ * varinfo_t ;
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 void** pointer_map_contains (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vi_for_tree ; 

__attribute__((used)) static varinfo_t
lookup_vi_for_tree (tree t)
{
  void **slot = pointer_map_contains (vi_for_tree, t);
  if (slot == NULL)
    return NULL;

  return (varinfo_t) *slot;
}