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
struct dom_info {int /*<<< orphan*/  fake_exit_edge; int /*<<< orphan*/  dfs_to_bb; int /*<<< orphan*/  dfs_order; int /*<<< orphan*/  set_child; int /*<<< orphan*/  set_size; int /*<<< orphan*/  set_chain; int /*<<< orphan*/  next_bucket; int /*<<< orphan*/  bucket; int /*<<< orphan*/  dom; int /*<<< orphan*/  key; int /*<<< orphan*/  path_min; int /*<<< orphan*/  dfs_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_dom_info (struct dom_info *di)
{
  free (di->dfs_parent);
  free (di->path_min);
  free (di->key);
  free (di->dom);
  free (di->bucket);
  free (di->next_bucket);
  free (di->set_chain);
  free (di->set_size);
  free (di->set_child);
  free (di->dfs_order);
  free (di->dfs_to_bb);
  BITMAP_FREE (di->fake_exit_edge);
}