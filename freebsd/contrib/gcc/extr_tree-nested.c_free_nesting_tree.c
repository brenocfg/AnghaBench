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
struct nesting_info {struct nesting_info* next; int /*<<< orphan*/  var_map; struct nesting_info* inner; } ;

/* Variables and functions */
 int /*<<< orphan*/  ggc_free (struct nesting_info*) ; 
 int /*<<< orphan*/  htab_delete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_nesting_tree (struct nesting_info *root)
{
  struct nesting_info *next;
  do
    {
      if (root->inner)
	free_nesting_tree (root->inner);
      htab_delete (root->var_map);
      next = root->next;
      ggc_free (root);
      root = next;
    }
  while (root);
}