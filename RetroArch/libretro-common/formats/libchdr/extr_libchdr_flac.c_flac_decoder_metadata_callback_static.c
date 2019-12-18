#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  channels; int /*<<< orphan*/  bits_per_sample; int /*<<< orphan*/  sample_rate; } ;
typedef  TYPE_3__ flac_decoder ;
struct TYPE_7__ {int /*<<< orphan*/  channels; int /*<<< orphan*/  bits_per_sample; int /*<<< orphan*/  sample_rate; } ;
struct TYPE_6__ {TYPE_2__ stream_info; } ;
struct TYPE_9__ {scalar_t__ type; TYPE_1__ data; } ;
typedef  TYPE_4__ FLAC__StreamMetadata ;
typedef  int /*<<< orphan*/  FLAC__StreamDecoder ;

/* Variables and functions */
 scalar_t__ FLAC__METADATA_TYPE_STREAMINFO ; 

void flac_decoder_metadata_callback_static(const FLAC__StreamDecoder *decoder, const FLAC__StreamMetadata *metadata, void *client_data)
{
   flac_decoder *fldecoder;
	/* ignore all but STREAMINFO metadata */
	if (metadata->type != FLAC__METADATA_TYPE_STREAMINFO)
		return;

	/* parse out the data we care about */
	fldecoder = (flac_decoder *)(client_data);
	fldecoder->sample_rate = metadata->data.stream_info.sample_rate;
	fldecoder->bits_per_sample = metadata->data.stream_info.bits_per_sample;
	fldecoder->channels = metadata->data.stream_info.channels;
}