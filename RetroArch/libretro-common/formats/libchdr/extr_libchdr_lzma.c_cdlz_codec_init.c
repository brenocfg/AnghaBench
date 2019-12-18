#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ chd_error ;
struct TYPE_2__ {int /*<<< orphan*/  subcode_decompressor; int /*<<< orphan*/  base_decompressor; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ cdlz_codec_data ;

/* Variables and functions */
 int CD_FRAME_SIZE ; 
 int CD_MAX_SECTOR_DATA ; 
 scalar_t__ CHDERR_NONE ; 
 scalar_t__ CHDERR_OUT_OF_MEMORY ; 
 scalar_t__ lzma_codec_init (int /*<<< orphan*/ *,int) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ zlib_codec_init (int /*<<< orphan*/ *,int) ; 

chd_error cdlz_codec_init(void* codec, uint32_t hunkbytes)
{
	chd_error ret;
	cdlz_codec_data* cdlz = (cdlz_codec_data*) codec;

	/* allocate buffer */
	cdlz->buffer = (uint8_t*)malloc(sizeof(uint8_t) * hunkbytes);
	if (cdlz->buffer == NULL)
		return CHDERR_OUT_OF_MEMORY;

	ret = lzma_codec_init(&cdlz->base_decompressor, (hunkbytes / CD_FRAME_SIZE) * CD_MAX_SECTOR_DATA);
	if (ret != CHDERR_NONE)
		return ret;

#ifdef WANT_SUBCODE
	ret = zlib_codec_init(&cdlz->subcode_decompressor, (hunkbytes / CD_FRAME_SIZE) * CD_MAX_SECTOR_DATA);
	if (ret != CHDERR_NONE)
		return ret;
#endif

	return CHDERR_NONE;
}