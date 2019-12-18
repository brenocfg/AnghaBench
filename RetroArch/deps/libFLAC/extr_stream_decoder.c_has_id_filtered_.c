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
struct TYPE_5__ {TYPE_1__* private_; } ;
struct TYPE_4__ {size_t metadata_filter_ids_count; scalar_t__ metadata_filter_ids; } ;
typedef  int /*<<< orphan*/  FLAC__byte ;
typedef  int FLAC__bool ;
typedef  TYPE_2__ FLAC__StreamDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__ASSERT (int) ; 
 int FLAC__STREAM_METADATA_APPLICATION_ID_LEN ; 
 scalar_t__ memcmp (scalar_t__,int /*<<< orphan*/ *,int) ; 

FLAC__bool has_id_filtered_(FLAC__StreamDecoder *decoder, FLAC__byte *id)
{
	size_t i;

	FLAC__ASSERT(0 != decoder);
	FLAC__ASSERT(0 != decoder->private_);

	for(i = 0; i < decoder->private_->metadata_filter_ids_count; i++)
		if(0 == memcmp(decoder->private_->metadata_filter_ids + i * (FLAC__STREAM_METADATA_APPLICATION_ID_LEN/8), id, (FLAC__STREAM_METADATA_APPLICATION_ID_LEN/8)))
			return true;

	return false;
}