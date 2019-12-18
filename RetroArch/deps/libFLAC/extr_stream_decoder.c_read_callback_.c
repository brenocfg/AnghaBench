#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* protected_; TYPE_1__* private_; } ;
struct TYPE_9__ {void* state; } ;
struct TYPE_8__ {int unparseable_frame_count; scalar_t__ (* read_callback ) (TYPE_3__*,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  client_data; scalar_t__ (* eof_callback ) (TYPE_3__*,int /*<<< orphan*/ ) ;scalar_t__ is_ogg; scalar_t__ is_seeking; } ;
typedef  int /*<<< orphan*/  FLAC__byte ;
typedef  int FLAC__bool ;
typedef  scalar_t__ FLAC__StreamDecoderReadStatus ;
typedef  TYPE_3__ FLAC__StreamDecoder ;

/* Variables and functions */
 void* FLAC__STREAM_DECODER_ABORTED ; 
 void* FLAC__STREAM_DECODER_END_OF_STREAM ; 
 scalar_t__ const FLAC__STREAM_DECODER_READ_STATUS_ABORT ; 
 scalar_t__ const FLAC__STREAM_DECODER_READ_STATUS_END_OF_STREAM ; 
 scalar_t__ read_callback_ogg_aspect_ (TYPE_3__*,int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (TYPE_3__*,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (TYPE_3__*,int /*<<< orphan*/ ) ; 

FLAC__bool read_callback_(FLAC__byte buffer[], size_t *bytes, void *client_data)
{
	FLAC__StreamDecoder *decoder = (FLAC__StreamDecoder *)client_data;

	if(
#if FLAC__HAS_OGG
		/* see [1] HACK NOTE below for why we don't call the eof_callback when decoding Ogg FLAC */
		!decoder->private_->is_ogg &&
#endif
		decoder->private_->eof_callback && decoder->private_->eof_callback(decoder, decoder->private_->client_data)
	) {
		*bytes = 0;
		decoder->protected_->state = FLAC__STREAM_DECODER_END_OF_STREAM;
		return false;
	}
	else if(*bytes > 0) {
		/* While seeking, it is possible for our seek to land in the
		 * middle of audio data that looks exactly like a frame header
		 * from a future version of an encoder.  When that happens, our
		 * error callback will get an
		 * FLAC__STREAM_DECODER_UNPARSEABLE_STREAM and increment its
		 * unparseable_frame_count.  But there is a remote possibility
		 * that it is properly synced at such a "future-codec frame",
		 * so to make sure, we wait to see many "unparseable" errors in
		 * a row before bailing out.
		 */
		if(decoder->private_->is_seeking && decoder->private_->unparseable_frame_count > 20) {
			decoder->protected_->state = FLAC__STREAM_DECODER_ABORTED;
			return false;
		}
		else {
			const FLAC__StreamDecoderReadStatus status =
#if FLAC__HAS_OGG
				decoder->private_->is_ogg?
				read_callback_ogg_aspect_(decoder, buffer, bytes) :
#endif
				decoder->private_->read_callback(decoder, buffer, bytes, decoder->private_->client_data)
			;
			if(status == FLAC__STREAM_DECODER_READ_STATUS_ABORT) {
				decoder->protected_->state = FLAC__STREAM_DECODER_ABORTED;
				return false;
			}
			else if(*bytes == 0) {
				if(
					status == FLAC__STREAM_DECODER_READ_STATUS_END_OF_STREAM ||
					(
#if FLAC__HAS_OGG
						/* see [1] HACK NOTE below for why we don't call the eof_callback when decoding Ogg FLAC */
						!decoder->private_->is_ogg &&
#endif
						decoder->private_->eof_callback && decoder->private_->eof_callback(decoder, decoder->private_->client_data)
					)
				) {
					decoder->protected_->state = FLAC__STREAM_DECODER_END_OF_STREAM;
					return false;
				}
				else
					return true;
			}
			else
				return true;
		}
	}
	else {
		/* abort to avoid a deadlock */
		decoder->protected_->state = FLAC__STREAM_DECODER_ABORTED;
		return false;
	}
	/* [1] @@@ HACK NOTE: The end-of-stream checking has to be hacked around
	 * for Ogg FLAC.  This is because the ogg decoder aspect can lose sync
	 * and at the same time hit the end of the stream (for example, seeking
	 * to a point that is after the beginning of the last Ogg page).  There
	 * is no way to report an Ogg sync loss through the callbacks (see note
	 * in read_callback_ogg_aspect_()) so it returns CONTINUE with *bytes==0.
	 * So to keep the decoder from stopping at this point we gate the call
	 * to the eof_callback and let the Ogg decoder aspect set the
	 * end-of-stream state when it is needed.
	 */
}