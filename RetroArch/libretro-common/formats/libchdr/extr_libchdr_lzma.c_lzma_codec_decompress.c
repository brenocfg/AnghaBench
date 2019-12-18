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
typedef  size_t uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  decoder; } ;
typedef  TYPE_1__ lzma_codec_data ;
typedef  int /*<<< orphan*/  chd_error ;
typedef  scalar_t__ SRes ;
typedef  int /*<<< orphan*/  ELzmaStatus ;

/* Variables and functions */
 int /*<<< orphan*/  CHDERR_DECOMPRESSION_ERROR ; 
 int /*<<< orphan*/  CHDERR_NONE ; 
 int /*<<< orphan*/  LZMA_FINISH_END ; 
 scalar_t__ LZMA_STATUS_MAYBE_FINISHED_WITHOUT_MARK ; 
 scalar_t__ LzmaDec_DecodeToBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/  const*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LzmaDec_Init (int /*<<< orphan*/ *) ; 
 scalar_t__ SZ_OK ; 

chd_error lzma_codec_decompress(void* codec, const uint8_t *src, uint32_t complen, uint8_t *dest, uint32_t destlen)
{
	ELzmaStatus status;
   SRes res;
   size_t consumedlen, decodedlen;
	/* initialize */
	lzma_codec_data* lzma_codec = (lzma_codec_data*) codec;
	LzmaDec_Init(&lzma_codec->decoder);

	/* decode */
	consumedlen = complen;
	decodedlen = destlen;
	res = LzmaDec_DecodeToBuf(&lzma_codec->decoder, dest, &decodedlen, src, &consumedlen, LZMA_FINISH_END, &status);
	if ((res != SZ_OK && res != LZMA_STATUS_MAYBE_FINISHED_WITHOUT_MARK) || consumedlen != complen || decodedlen != destlen)
		return CHDERR_DECOMPRESSION_ERROR;
	return CHDERR_NONE;
}