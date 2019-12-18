#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * decoder; } ;
typedef  TYPE_1__ flac_decoder ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__stream_decoder_delete (int /*<<< orphan*/ *) ; 

void flac_decoder_free(flac_decoder* decoder)
{
	if ((decoder != NULL) && (decoder->decoder != NULL))
		FLAC__stream_decoder_delete(decoder->decoder);
}