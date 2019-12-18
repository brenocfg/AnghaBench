#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int length_lo; int length_hi; int aux_lo; int aux_hi; } ;
struct TYPE_5__ {int block_length; size_t current_block; size_t num_blocks; int* block_offsets; int* buffer; int /*<<< orphan*/  file; scalar_t__ isCAS; } ;
typedef  TYPE_1__ IMG_TAPE_t ;
typedef  TYPE_2__ CAS_Header ;

/* Variables and functions */
 int /*<<< orphan*/  EnlargeBuffer (TYPE_1__*,int) ; 
 int FALSE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int SIO_ChkSum (int*,int) ; 
 int TRUE ; 
 int fread (int*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ fseek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ReadNextRecord(IMG_TAPE_t *file, int *gap)
{
	int length;

	/* 0 indicates that there was no previous block being read and
	   current_block already contains the current block number. */
	if (file->block_length != 0) {
		/* Non-zero - a block was being read and it's finished, increase the block number. */
		file->block_length = 0;
		if (++file->current_block >= file->num_blocks)
			/* Last block was already read. */
			return FALSE;
	}

	if (file->isCAS) {
		CAS_Header header;

		/* While reading a block, offset by 4 to skip its 4-byte name (assume it's "data") */
		if (fseek(file->file, file->block_offsets[file->current_block] + 4, SEEK_SET) != 0
		    || fread(&header.length_lo, 1, 4, file->file) < 4)
			return FALSE;
		length = header.length_lo + (header.length_hi << 8);
		*gap = header.aux_lo + (header.aux_hi << 8);
		/* read block into buffer */
		EnlargeBuffer(file, length);
		if (fread(file->buffer, 1, length, file->file) < length)
			return FALSE;
	}
	else {
		length = 132;
		/* Don't enlarge buffer - its default size is at least 132. */
		*gap = (file->current_block == 0 ? 19200 : 260);
		file->buffer[0] = 0x55;
		file->buffer[1] = 0x55;
		if (file->current_block + 1 >= file->num_blocks) {
			/* EOF record */
			file->buffer[2] = 0xfe;
			memset(file->buffer + 3, 0, 128);
		}
		else {
			int bytes;
			if (fseek(file->file, file->current_block * 128, SEEK_SET) != 0
			    || (bytes = fread(file->buffer + 3, 1, 128, file->file)) == 0)
				return FALSE;
			if (bytes < 128) {
				file->buffer[2] = 0xfa; /* non-full record */
				memset(file->buffer + 3 + bytes, 0, 127 - bytes);
				file->buffer[0x82] = bytes;
			}
			else
				file->buffer[2] = 0xfc;	/* full record */
		}
		file->buffer[0x83] = SIO_ChkSum(file->buffer, 0x83);
	}
	file->block_length = length;
	return TRUE;
}