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
typedef  void* tree ;
struct dcast_data_s {void* offset; scalar_t__ repeated_base; scalar_t__ virt_depth; int /*<<< orphan*/  subtype; } ;

/* Variables and functions */
 void* BINFO_OFFSET (void*) ; 
 int /*<<< orphan*/  BINFO_TYPE (void*) ; 
 scalar_t__ BINFO_VIRTUAL_P (void*) ; 
 void* NULL_TREE ; 
 scalar_t__ SAME_BINFO_TYPE_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* dfs_skip_bases ; 
 void* ssize_int (int) ; 

__attribute__((used)) static tree
dfs_dcast_hint_pre (tree binfo, void *data_)
{
  struct dcast_data_s *data = (struct dcast_data_s *) data_;

  if (BINFO_VIRTUAL_P (binfo))
    data->virt_depth++;

  if (SAME_BINFO_TYPE_P (BINFO_TYPE (binfo), data->subtype))
    {
      if (data->virt_depth)
	{
	  data->offset = ssize_int (-1);
	  return data->offset;
	}
      if (data->offset)
	data->offset = ssize_int (-3);
      else
	data->offset = BINFO_OFFSET (binfo);

      return data->repeated_base ? dfs_skip_bases : data->offset;
    }

  return NULL_TREE;
}