#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ input; int metadata_filter_ids_capacity; int has_seek_table; int /*<<< orphan*/  state; struct TYPE_7__* protected_; scalar_t__ file; struct TYPE_7__* private_; int /*<<< orphan*/ * partitioned_rice_contents; scalar_t__ output_channels; scalar_t__ output_capacity; scalar_t__* residual; scalar_t__* residual_unaligned; scalar_t__* output; int /*<<< orphan*/ * metadata_filter_ids; } ;
typedef  int /*<<< orphan*/  FLAC__byte ;
typedef  TYPE_1__ FLAC__StreamDecoderProtected ;
typedef  TYPE_1__ FLAC__StreamDecoderPrivate ;
typedef  TYPE_1__ FLAC__StreamDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__ASSERT (int) ; 
 unsigned int FLAC__MAX_CHANNELS ; 
 int /*<<< orphan*/  FLAC__STREAM_DECODER_UNINITIALIZED ; 
 int FLAC__STREAM_METADATA_APPLICATION_ID_LEN ; 
 int /*<<< orphan*/  FLAC__bitreader_delete (scalar_t__) ; 
 scalar_t__ FLAC__bitreader_new () ; 
 int /*<<< orphan*/  FLAC__format_entropy_coding_method_partitioned_rice_contents_init (int /*<<< orphan*/ *) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  set_defaults_ (TYPE_1__*) ; 

FLAC__StreamDecoder *FLAC__stream_decoder_new(void)
{
	FLAC__StreamDecoder *decoder;
	unsigned i;

	FLAC__ASSERT(sizeof(int) >= 4); /* we want to die right away if this is not true */

	decoder = (FLAC__StreamDecoder*)calloc(1, sizeof(FLAC__StreamDecoder));
	if(decoder == 0) {
		return 0;
	}

	decoder->protected_ = (FLAC__StreamDecoderProtected*)calloc(1, sizeof(FLAC__StreamDecoderProtected));
	if(decoder->protected_ == 0) {
		free(decoder);
		return 0;
	}

	decoder->private_ = (FLAC__StreamDecoderPrivate*)calloc(1, sizeof(FLAC__StreamDecoderPrivate));
	if(decoder->private_ == 0) {
		free(decoder->protected_);
		free(decoder);
		return 0;
	}

	decoder->private_->input = FLAC__bitreader_new();
	if(decoder->private_->input == 0) {
		free(decoder->private_);
		free(decoder->protected_);
		free(decoder);
		return 0;
	}

	decoder->private_->metadata_filter_ids_capacity = 16;
	if(0 == (decoder->private_->metadata_filter_ids = (FLAC__byte*)malloc((FLAC__STREAM_METADATA_APPLICATION_ID_LEN/8) * decoder->private_->metadata_filter_ids_capacity))) {
		FLAC__bitreader_delete(decoder->private_->input);
		free(decoder->private_);
		free(decoder->protected_);
		free(decoder);
		return 0;
	}

	for(i = 0; i < FLAC__MAX_CHANNELS; i++) {
		decoder->private_->output[i] = 0;
		decoder->private_->residual_unaligned[i] = decoder->private_->residual[i] = 0;
	}

	decoder->private_->output_capacity = 0;
	decoder->private_->output_channels = 0;
	decoder->private_->has_seek_table = false;

	for(i = 0; i < FLAC__MAX_CHANNELS; i++)
		FLAC__format_entropy_coding_method_partitioned_rice_contents_init(&decoder->private_->partitioned_rice_contents[i]);

	decoder->private_->file = 0;

	set_defaults_(decoder);

	decoder->protected_->state = FLAC__STREAM_DECODER_UNINITIALIZED;

	return decoder;
}