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
typedef  int /*<<< orphan*/  UWORD ;
struct TYPE_5__ {int save_gap; int block_length; int /*<<< orphan*/ * buffer; scalar_t__ was_writing; scalar_t__ next_blockbyte; scalar_t__ savetime; } ;
typedef  TYPE_1__ IMG_TAPE_t ;

/* Variables and functions */
 int /*<<< orphan*/  EnlargeBuffer (TYPE_1__*,int) ; 
 int /*<<< orphan*/  MEMORY_CopyFromMem (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SIO_ChkSum (int /*<<< orphan*/ *,int) ; 
 scalar_t__ TRUE ; 
 int WriteRecord (TYPE_1__*) ; 

int IMG_TAPE_WriteFromMemory(IMG_TAPE_t *file, UWORD src_addr, int length, int gap)
{
	if (!file->was_writing) {
		file->savetime = 0;
		file->save_gap = 0;
		file->next_blockbyte = 0;
		file->block_length = 0;
		file->was_writing = TRUE;
	}
	EnlargeBuffer(file, length + 1);
	/* Put record into buffer. */
	MEMORY_CopyFromMem(src_addr, file->buffer, length);
	/* Eval checksum over buffer data. */
	file->buffer[length] = SIO_ChkSum(file->buffer, length);
	file->save_gap = gap;
	file->block_length = length + 1;
	return WriteRecord(file);
}