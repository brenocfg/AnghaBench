#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_8__* protected_; TYPE_7__* private_; } ;
struct TYPE_19__ {scalar_t__ state; int /*<<< orphan*/  ogg_decoder_aspect; } ;
struct TYPE_15__ {int /*<<< orphan*/  md5sum; } ;
struct TYPE_16__ {TYPE_4__ stream_info; } ;
struct TYPE_17__ {TYPE_5__ data; } ;
struct TYPE_12__ {scalar_t__ points; } ;
struct TYPE_13__ {TYPE_1__ seek_table; } ;
struct TYPE_14__ {TYPE_2__ data; } ;
struct TYPE_18__ {int has_seek_table; scalar_t__* output; scalar_t__* residual_unaligned; scalar_t__* residual; scalar_t__ file; int is_seeking; int /*<<< orphan*/  computed_md5sum; TYPE_6__ stream_info; scalar_t__ do_md5_checking; scalar_t__ is_ogg; scalar_t__ output_channels; scalar_t__ output_capacity; int /*<<< orphan*/  input; TYPE_3__ seek_table; int /*<<< orphan*/  md5context; } ;
typedef  int FLAC__bool ;
typedef  TYPE_9__ FLAC__StreamDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__ASSERT (int) ; 
 unsigned int FLAC__MAX_CHANNELS ; 
 int /*<<< orphan*/  FLAC__MD5Final (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ FLAC__STREAM_DECODER_UNINITIALIZED ; 
 int /*<<< orphan*/  FLAC__bitreader_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLAC__ogg_decoder_aspect_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_defaults_ (TYPE_9__*) ; 
 scalar_t__ stdin ; 

FLAC__bool FLAC__stream_decoder_finish(FLAC__StreamDecoder *decoder)
{
	FLAC__bool md5_failed = false;
	unsigned i;

	FLAC__ASSERT(0 != decoder);
	FLAC__ASSERT(0 != decoder->private_);
	FLAC__ASSERT(0 != decoder->protected_);

	if(decoder->protected_->state == FLAC__STREAM_DECODER_UNINITIALIZED)
		return true;

	/* see the comment in FLAC__stream_decoder_reset() as to why we
	 * always call FLAC__MD5Final()
	 */
	FLAC__MD5Final(decoder->private_->computed_md5sum, &decoder->private_->md5context);

	free(decoder->private_->seek_table.data.seek_table.points);
	decoder->private_->seek_table.data.seek_table.points = 0;
	decoder->private_->has_seek_table = false;

	FLAC__bitreader_free(decoder->private_->input);
	for(i = 0; i < FLAC__MAX_CHANNELS; i++) {
		/* WATCHOUT:
		 * FLAC__lpc_restore_signal_asm_ia32_mmx() requires that the
		 * output arrays have a buffer of up to 3 zeroes in front
		 * (at negative indices) for alignment purposes; we use 4
		 * to keep the data well-aligned.
		 */
		if(0 != decoder->private_->output[i]) {
			free(decoder->private_->output[i]-4);
			decoder->private_->output[i] = 0;
		}
		if(0 != decoder->private_->residual_unaligned[i]) {
			free(decoder->private_->residual_unaligned[i]);
			decoder->private_->residual_unaligned[i] = decoder->private_->residual[i] = 0;
		}
	}
	decoder->private_->output_capacity = 0;
	decoder->private_->output_channels = 0;

#if FLAC__HAS_OGG
	if(decoder->private_->is_ogg)
		FLAC__ogg_decoder_aspect_finish(&decoder->protected_->ogg_decoder_aspect);
#endif

	if(0 != decoder->private_->file) {
		if(decoder->private_->file != stdin)
			fclose(decoder->private_->file);
		decoder->private_->file = 0;
	}

	if(decoder->private_->do_md5_checking) {
		if(memcmp(decoder->private_->stream_info.data.stream_info.md5sum, decoder->private_->computed_md5sum, 16))
			md5_failed = true;
	}
	decoder->private_->is_seeking = false;

	set_defaults_(decoder);

	decoder->protected_->state = FLAC__STREAM_DECODER_UNINITIALIZED;

	return !md5_failed;
}