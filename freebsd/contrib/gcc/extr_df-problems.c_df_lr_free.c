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
struct df_lr_bb_info {int /*<<< orphan*/  out; int /*<<< orphan*/  in; int /*<<< orphan*/  def; int /*<<< orphan*/  use; } ;
struct dataflow {unsigned int block_info_size; struct dataflow* problem_data; struct dataflow* block_info; int /*<<< orphan*/  block_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_FREE (int /*<<< orphan*/ ) ; 
 struct df_lr_bb_info* df_lr_get_bb_info (struct dataflow*,unsigned int) ; 
 int /*<<< orphan*/  free (struct dataflow*) ; 
 int /*<<< orphan*/  free_alloc_pool (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
df_lr_free (struct dataflow *dflow)
{
  if (dflow->block_info)
    {
      unsigned int i;
      for (i = 0; i < dflow->block_info_size; i++)
	{
	  struct df_lr_bb_info *bb_info = df_lr_get_bb_info (dflow, i);
	  if (bb_info)
	    {
	      BITMAP_FREE (bb_info->use);
	      BITMAP_FREE (bb_info->def);
	      BITMAP_FREE (bb_info->in);
	      BITMAP_FREE (bb_info->out);
	    }
	}
      free_alloc_pool (dflow->block_pool);
      
      dflow->block_info_size = 0;
      free (dflow->block_info);
    }

  free (dflow->problem_data);
  free (dflow);
}