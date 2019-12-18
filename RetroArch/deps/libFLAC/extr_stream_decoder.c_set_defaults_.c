#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* protected_; TYPE_1__* private_; } ;
struct TYPE_6__ {int md5_checking; int /*<<< orphan*/  ogg_decoder_aspect; } ;
struct TYPE_5__ {int is_ogg; int* metadata_filter; scalar_t__ metadata_filter_ids_count; scalar_t__ client_data; scalar_t__ error_callback; scalar_t__ metadata_callback; scalar_t__ write_callback; scalar_t__ eof_callback; scalar_t__ length_callback; scalar_t__ tell_callback; scalar_t__ seek_callback; scalar_t__ read_callback; } ;
typedef  TYPE_3__ FLAC__StreamDecoder ;

/* Variables and functions */
 size_t FLAC__METADATA_TYPE_STREAMINFO ; 
 int /*<<< orphan*/  FLAC__ogg_decoder_aspect_set_defaults (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

void set_defaults_(FLAC__StreamDecoder *decoder)
{
	decoder->private_->is_ogg = false;
	decoder->private_->read_callback = 0;
	decoder->private_->seek_callback = 0;
	decoder->private_->tell_callback = 0;
	decoder->private_->length_callback = 0;
	decoder->private_->eof_callback = 0;
	decoder->private_->write_callback = 0;
	decoder->private_->metadata_callback = 0;
	decoder->private_->error_callback = 0;
	decoder->private_->client_data = 0;

	memset(decoder->private_->metadata_filter, 0, sizeof(decoder->private_->metadata_filter));
	decoder->private_->metadata_filter[FLAC__METADATA_TYPE_STREAMINFO] = true;
	decoder->private_->metadata_filter_ids_count = 0;

	decoder->protected_->md5_checking = false;

#if FLAC__HAS_OGG
	FLAC__ogg_decoder_aspect_set_defaults(&decoder->protected_->ogg_decoder_aspect);
#endif
}