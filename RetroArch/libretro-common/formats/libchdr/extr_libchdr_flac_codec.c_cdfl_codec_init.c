#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  scalar_t__ chd_error ;
struct TYPE_4__ {int /*<<< orphan*/ * decoder; } ;
struct TYPE_3__ {int* buffer; int swap_endian; TYPE_2__ decoder; int /*<<< orphan*/  subcode_decompressor; } ;
typedef  TYPE_1__ cdfl_codec_data ;

/* Variables and functions */
 int CD_FRAME_SIZE ; 
 int CD_MAX_SECTOR_DATA ; 
 scalar_t__ CHDERR_CODEC_ERROR ; 
 scalar_t__ CHDERR_NONE ; 
 scalar_t__ CHDERR_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  flac_decoder_init (TYPE_2__*) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ zlib_codec_init (int /*<<< orphan*/ *,int) ; 

chd_error cdfl_codec_init(void *codec, uint32_t hunkbytes)
{
#ifdef WANT_SUBCODE
   chd_error ret;
#endif
   uint16_t native_endian = 0;
	cdfl_codec_data *cdfl = (cdfl_codec_data*)codec;

	/* make sure the CHD's hunk size is an even multiple of the frame size */
	if (hunkbytes % CD_FRAME_SIZE != 0)
		return CHDERR_CODEC_ERROR;

	cdfl->buffer = (uint8_t*)malloc(sizeof(uint8_t) * hunkbytes);
	if (cdfl->buffer == NULL)
		return CHDERR_OUT_OF_MEMORY;

	/* determine whether we want native or swapped samples */
	*(uint8_t *)(&native_endian) = 1;
	cdfl->swap_endian = (native_endian & 1);

#ifdef WANT_SUBCODE
	/* init zlib inflater */
	ret = zlib_codec_init(&cdfl->subcode_decompressor, (hunkbytes / CD_FRAME_SIZE) * CD_MAX_SECTOR_DATA);
	if (ret != CHDERR_NONE)
		return ret;
#endif

	/* flac decoder init */
	flac_decoder_init(&cdfl->decoder);
	if (cdfl->decoder.decoder == NULL)
		return CHDERR_OUT_OF_MEMORY;

	return CHDERR_NONE;
}