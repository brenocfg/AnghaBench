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
struct nesting_info {struct nesting_info* next; struct nesting_info* inner; } ;

/* Variables and functions */
 int /*<<< orphan*/  unnest_nesting_tree_1 (struct nesting_info*) ; 

__attribute__((used)) static void
unnest_nesting_tree (struct nesting_info *root)
{
  do
    {
      if (root->inner)
	unnest_nesting_tree (root->inner);
      unnest_nesting_tree_1 (root);
      root = root->next;
    }
  while (root);
}