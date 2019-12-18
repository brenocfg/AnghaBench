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
struct dataflow {unsigned int block_info_size; int /*<<< orphan*/  block_info; } ;

/* Variables and functions */
 int last_basic_block ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  xrealloc (int /*<<< orphan*/ ,unsigned int) ; 

void
df_grow_bb_info (struct dataflow *dflow)
{
  unsigned int new_size = last_basic_block + 1;
  if (dflow->block_info_size < new_size)
    {
      new_size += new_size / 4;
      dflow->block_info = xrealloc (dflow->block_info, 
				    new_size *sizeof (void*));
      memset (dflow->block_info + dflow->block_info_size, 0,
	      (new_size - dflow->block_info_size) *sizeof (void *));
      dflow->block_info_size = new_size;
    }
}