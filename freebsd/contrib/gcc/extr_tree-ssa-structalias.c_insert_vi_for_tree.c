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
typedef  void* varinfo_t ;
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  gcc_assert (void*) ; 
 void** pointer_map_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vi_for_tree ; 

__attribute__((used)) static void
insert_vi_for_tree (tree t, varinfo_t vi)
{
  void **slot = pointer_map_insert (vi_for_tree, t);
  gcc_assert (vi);
  gcc_assert (*slot == NULL);
  *slot = vi;
}