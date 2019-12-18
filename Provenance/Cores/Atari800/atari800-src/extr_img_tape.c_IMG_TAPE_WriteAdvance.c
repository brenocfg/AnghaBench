#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ savetime; int /*<<< orphan*/  num_blocks; int /*<<< orphan*/  current_block; scalar_t__ was_writing; scalar_t__ block_length; scalar_t__ next_blockbyte; scalar_t__ save_gap; } ;
typedef  TYPE_1__ IMG_TAPE_t ;

/* Variables and functions */
 scalar_t__ TRUE ; 

void IMG_TAPE_WriteAdvance(IMG_TAPE_t *file, unsigned int num_ticks)
{
	if (!file->was_writing) {
		file->savetime = 0;
		file->save_gap = 0;
		file->next_blockbyte = 0;
		file->block_length = 0;
		file->was_writing = TRUE;
		/* Always append to end of file. */
		file->current_block = file->num_blocks;
	}
	file->savetime += num_ticks;
}