#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int was_writing; scalar_t__ next_blockbyte; scalar_t__ block_length; int* block_baudrates; size_t current_block; scalar_t__ isCAS; } ;
typedef  TYPE_1__ IMG_TAPE_t ;

/* Variables and functions */
 int /*<<< orphan*/  CassetteFlush (TYPE_1__*) ; 
 int FALSE ; 
 int /*<<< orphan*/  ReadNextRecord (TYPE_1__*,int*) ; 
 int TRUE ; 

int IMG_TAPE_SkipToData(IMG_TAPE_t *file, int ms)
{
	if (file->was_writing) {
		CassetteFlush(file);
		file->was_writing = FALSE;
	}

	while (ms > 0) {
		if (file->next_blockbyte < file->block_length) {
			int bytes = ms * (file->isCAS ? file->block_baudrates[file->current_block] : 600) / 1000 / 10;
			if (bytes > file->block_length - file->next_blockbyte)
				bytes = file->block_length - file->next_blockbyte;
			file->next_blockbyte += bytes;
			ms -= bytes * 10 * 1000 / (file->isCAS ? file->block_baudrates[file->current_block] : 600);
			continue;
		}
		else {
			int gap;
			if (!ReadNextRecord(file, &gap))
				return FALSE;
			file->next_blockbyte = 0;
			ms -= gap;
		}
	}
	return TRUE;
}