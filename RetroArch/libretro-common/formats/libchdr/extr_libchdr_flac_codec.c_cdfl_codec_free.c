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
struct TYPE_2__ {scalar_t__ buffer; int /*<<< orphan*/  subcode_decompressor; int /*<<< orphan*/  decoder; } ;
typedef  TYPE_1__ cdfl_codec_data ;

/* Variables and functions */
 int /*<<< orphan*/  flac_decoder_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  zlib_codec_free (int /*<<< orphan*/ *) ; 

void cdfl_codec_free(void *codec)
{
	cdfl_codec_data *cdfl = (cdfl_codec_data*)codec;
	flac_decoder_free(&cdfl->decoder);
#ifdef WANT_SUBCODE
	zlib_codec_free(&cdfl->subcode_decompressor);
#endif
	if (cdfl->buffer)
		free(cdfl->buffer);
}