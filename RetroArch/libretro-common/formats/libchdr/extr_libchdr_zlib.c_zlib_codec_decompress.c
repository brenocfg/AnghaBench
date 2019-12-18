#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ total_out; scalar_t__ avail_out; int /*<<< orphan*/ * next_out; scalar_t__ total_in; scalar_t__ avail_in; int /*<<< orphan*/ * next_in; } ;
struct TYPE_4__ {TYPE_2__ inflater; } ;
typedef  TYPE_1__ zlib_codec_data ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  chd_error ;
typedef  int /*<<< orphan*/  Bytef ;

/* Variables and functions */
 int /*<<< orphan*/  CHDERR_DECOMPRESSION_ERROR ; 
 int /*<<< orphan*/  CHDERR_NONE ; 
 int /*<<< orphan*/  Z_FINISH ; 
 int Z_OK ; 
 int inflate (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int inflateReset (TYPE_2__*) ; 

chd_error zlib_codec_decompress(void *codec, const uint8_t *src, uint32_t complen, uint8_t *dest, uint32_t destlen)
{
	zlib_codec_data *data = (zlib_codec_data *)codec;
	int zerr;

	/* reset the decompressor */
	data->inflater.next_in = (Bytef *)src;
	data->inflater.avail_in = complen;
	data->inflater.total_in = 0;
	data->inflater.next_out = (Bytef *)dest;
	data->inflater.avail_out = destlen;
	data->inflater.total_out = 0;
	zerr = inflateReset(&data->inflater);
	if (zerr != Z_OK)
		return CHDERR_DECOMPRESSION_ERROR;

	/* do it */
	zerr = inflate(&data->inflater, Z_FINISH);
    (void)zerr;
	if (data->inflater.total_out != destlen)
		return CHDERR_DECOMPRESSION_ERROR;

	return CHDERR_NONE;
}