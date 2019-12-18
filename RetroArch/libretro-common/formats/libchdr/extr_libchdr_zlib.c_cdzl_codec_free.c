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
struct TYPE_2__ {scalar_t__ buffer; int /*<<< orphan*/  subcode_decompressor; int /*<<< orphan*/  base_decompressor; } ;
typedef  TYPE_1__ cdzl_codec_data ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  zlib_codec_free (int /*<<< orphan*/ *) ; 

void cdzl_codec_free(void *codec)
{
	cdzl_codec_data* cdzl = (cdzl_codec_data*)codec;

	zlib_codec_free(&cdzl->base_decompressor);
#ifdef WANT_SUBCODE
	zlib_codec_free(&cdzl->subcode_decompressor);
#endif
	if (cdzl->buffer)
		free(cdzl->buffer);
}