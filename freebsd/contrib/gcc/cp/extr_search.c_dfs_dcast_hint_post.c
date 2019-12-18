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
typedef  int /*<<< orphan*/  tree ;
struct dcast_data_s {int /*<<< orphan*/  virt_depth; } ;

/* Variables and functions */
 scalar_t__ BINFO_VIRTUAL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 

__attribute__((used)) static tree
dfs_dcast_hint_post (tree binfo, void *data_)
{
  struct dcast_data_s *data = (struct dcast_data_s *) data_;

  if (BINFO_VIRTUAL_P (binfo))
    data->virt_depth--;

  return NULL_TREE;
}