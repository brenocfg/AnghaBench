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
struct TYPE_6__ {int length_lo; int length_hi; int aux_lo; int aux_hi; int /*<<< orphan*/  identifier; } ;
struct TYPE_5__ {size_t num_blocks; int block_length; int save_gap; int current_block; int /*<<< orphan*/  file; TYPE_2__* buffer; scalar_t__* block_offsets; int /*<<< orphan*/ * block_baudrates; int /*<<< orphan*/  isCAS; } ;
typedef  TYPE_1__ IMG_TAPE_t ;
typedef  TYPE_2__ CAS_Header ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_BAUDRATE ; 
 int FALSE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  Util_strncpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ fseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int fwrite (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int WriteRecord(IMG_TAPE_t *file)
{
	CAS_Header header;
	int result;

	/* on a raw file, saving is denied because it can hold
	    only 1 file and could cause confusion */
	if (!file->isCAS)
		return FALSE;
	/* always append */
	if (fseek(file->file, file->block_offsets[file->num_blocks], SEEK_SET) != 0)
		return FALSE;
	/* write record header */
	Util_strncpy(header.identifier, "data", 4);
	header.length_lo = file->block_length & 0xFF;
	header.length_hi = (file->block_length >> 8) & 0xFF;
	header.aux_lo = file->save_gap & 0xff;
	header.aux_hi = (file->save_gap >> 8) & 0xff;
	if (fwrite(&header, 1, 8, file->file) != 8)
		return FALSE;
	/* Saving is supported only with standard baudrate. */
	file->block_baudrates[file->num_blocks] = DEFAULT_BAUDRATE;
	file->num_blocks++;
	file->block_offsets[file->num_blocks] = file->block_offsets[file->num_blocks - 1] + file->block_length + 8;
	file->current_block = file->num_blocks;
	/* write record */
	result = fwrite(file->buffer, 1, file->block_length, file->file) == file->block_length;
	if (result) {
		file->save_gap = 0;
		file->block_length = 0;
	}
	return result;
}