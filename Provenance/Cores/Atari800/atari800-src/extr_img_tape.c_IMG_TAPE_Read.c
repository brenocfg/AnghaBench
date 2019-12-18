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
typedef  int /*<<< orphan*/  UBYTE ;
struct TYPE_5__ {int was_writing; scalar_t__ next_blockbyte; scalar_t__ block_length; int* block_baudrates; size_t current_block; scalar_t__ isCAS; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ IMG_TAPE_t ;

/* Variables and functions */
 int /*<<< orphan*/  CassetteFlush (TYPE_1__*) ; 
 int FALSE ; 
 int /*<<< orphan*/  ReadNextRecord (TYPE_1__*,int*) ; 
 int TRUE ; 

int IMG_TAPE_Read(IMG_TAPE_t *file, unsigned int *duration, int *is_gap, UBYTE *byte)
{
	int gap;
	if (file->was_writing) {
		CassetteFlush(file);
		file->was_writing = FALSE;
	}
	if (file->next_blockbyte >= file->block_length) {
		/* Buffer is exhausted, load next record. */

		if (!ReadNextRecord(file, &gap))
			return FALSE;
		file->next_blockbyte = 0;
		if (gap > 0) {
			/* Convert gap from ms to CPU ticks. */
			*duration = gap * 1789 + gap * 790 / 1000; /* (gap * 1789790 / 1000), avoiding overflow */
			*is_gap = TRUE;
			return TRUE;
		}
	}
	*byte = file->buffer[file->next_blockbyte++];
	*is_gap = FALSE;
	/* Next event will be after 10 bits of data gets loaded. */
	*duration = 10 * 1789790 / (file->isCAS ? file->block_baudrates[file->current_block] : 600);
	return TRUE;
}