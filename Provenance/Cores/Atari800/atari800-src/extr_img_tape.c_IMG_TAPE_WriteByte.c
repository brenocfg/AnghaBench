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
struct TYPE_5__ {int savetime; scalar_t__ block_length; int save_gap; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ IMG_TAPE_t ;

/* Variables and functions */
 int /*<<< orphan*/  EnlargeBuffer (TYPE_1__*,scalar_t__) ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  WriteRecord (TYPE_1__*) ; 

int IMG_TAPE_WriteByte(IMG_TAPE_t *file, UBYTE byte, unsigned int pokey_counter)
{
	/* put_delay is time between end of last byte write / motor start, and
	   start of writing of current BYTE (in ms). */
	/* Note: byte duration in seconds: pokey_counter / (1789790/2) * 10
	 * in milliseconds: pokey_counter * 10 * 1000 / 1789790/2 */
	int put_delay = file->savetime /1790 - 10 * pokey_counter / 895; /* better accuracy not needed */
	if (put_delay > 05) {

		/* write previous block */
		if (file->block_length > 0) {
			if (!WriteRecord(file))
				return FALSE; /* Write error */
		}
		/* set new gap-time */
		file->save_gap += put_delay;
	}
	/* put byte into buffer */
	EnlargeBuffer(file, file->block_length + 1);
	file->buffer[file->block_length++] = byte;
	/* set new last byte-put time */
	file->savetime = 0;

	return TRUE;
}