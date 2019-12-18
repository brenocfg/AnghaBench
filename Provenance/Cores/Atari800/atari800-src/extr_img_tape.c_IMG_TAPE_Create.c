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
typedef  int /*<<< orphan*/  header ;
typedef  void* UBYTE ;
struct TYPE_6__ {char length_lo; int aux_lo; int aux_hi; void* length_hi; } ;
struct TYPE_5__ {int* block_offsets; int buffer_size; void* was_writing; void* buffer; scalar_t__ num_blocks; scalar_t__ current_block; scalar_t__ block_length; scalar_t__ next_blockbyte; scalar_t__ save_gap; scalar_t__ savetime; void* isCAS; int /*<<< orphan*/  description; int /*<<< orphan*/ * file; } ;
typedef  TYPE_1__ IMG_TAPE_t ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_2__ CAS_Header ;

/* Variables and functions */
 int /*<<< orphan*/  CASSETTE_DESCRIPTION_MAX ; 
 int DEFAULT_BAUDRATE ; 
 int DEFAULT_BUFFER_SIZE ; 
 void* TRUE ; 
 void* Util_malloc (int) ; 
 int /*<<< orphan*/  Util_strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fwrite (char const*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int strlen (char const*) ; 

IMG_TAPE_t *IMG_TAPE_Create(char const *filename, char const *description)
{
	IMG_TAPE_t *img;
	CAS_Header header;
	size_t desc_len;
	FILE *file = NULL;

	/* create new file */
	file = fopen(filename, "wb+");
	if (file == NULL)
		return NULL;

	/* Write the initial FUJI and baud blocks of the CAS file. */
	desc_len = strlen(description);
	memset(&header, 0, sizeof(header));
	/* write CAS-header */
	header.length_lo = (UBYTE) desc_len;
	header.length_hi = (UBYTE) (desc_len >> 8);
	if (fwrite("FUJI", 1, 4, file) != 4
	    || fwrite(&header.length_lo, 1, 4, file) != 4
	    || fwrite(description, 1, desc_len, file) != desc_len) {
		fclose(file);
		return NULL;
	}

	memset(&header, 0, sizeof(header));
	/* All records are written with 600 baud speed. */
	header.aux_lo = DEFAULT_BAUDRATE & 0xff;
	header.aux_hi = DEFAULT_BAUDRATE >> 8;
	if (fwrite("baud", 1, 4, file) != 4
	    || fwrite(&header.length_lo, 1, 4, file) != 4) {
		fclose(file);
		return NULL;
	}

	img = Util_malloc(sizeof(IMG_TAPE_t));
	img->file = file;
	if (description != NULL)
		Util_strlcpy(img->description, description, CASSETTE_DESCRIPTION_MAX);
	img->isCAS = TRUE;
	img->savetime = 0;
	img->save_gap = 0;
	img->next_blockbyte = 0;
	img->block_length = 0;
	img->current_block = 0;
	img->num_blocks = 0;
	img->block_offsets[0] = strlen(description) + 16;
	img->buffer = Util_malloc((img->buffer_size = DEFAULT_BUFFER_SIZE) * sizeof(UBYTE));
	img->was_writing = TRUE;

	return img;
}