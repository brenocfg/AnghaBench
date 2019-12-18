#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int mpc_uint32_t ;
typedef  int mpc_int64_t ;
struct TYPE_14__ {int samples; int bits; scalar_t__ buffer; int /*<<< orphan*/  is_key_frame; } ;
typedef  TYPE_1__ mpc_frame_info ;
struct TYPE_15__ {int samples; int decoded_samples; int stream_version; int samples_to_skip; int channels; } ;
typedef  TYPE_2__ mpc_decoder ;
struct TYPE_16__ {int buff; scalar_t__ count; } ;
typedef  TYPE_3__ mpc_bits_reader ;
typedef  int /*<<< orphan*/  MPC_SAMPLE_FORMAT ;

/* Variables and functions */
 int MPC_DECODER_SYNTH_DELAY ; 
 int MPC_FRAME_LENGTH ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 
 int mpc_bits_read (TYPE_3__*,int) ; 
 int /*<<< orphan*/  mpc_decoder_read_bitstream_sv7 (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  mpc_decoder_read_bitstream_sv8 (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc_decoder_requantisierung (TYPE_2__*) ; 
 int /*<<< orphan*/  mpc_decoder_synthese_filter_float (TYPE_2__*,scalar_t__,int) ; 

void mpc_decoder_decode_frame(mpc_decoder * d,
							  mpc_bits_reader * r,
							  mpc_frame_info * i)
{
	mpc_bits_reader r_sav = *r;
	mpc_int64_t samples_left;

	samples_left = d->samples - d->decoded_samples + MPC_DECODER_SYNTH_DELAY;

	if (samples_left <= 0 && d->samples != 0) {
		i->samples = 0;
		i->bits = -1;
		return;
	}

	if (d->stream_version == 8)
		mpc_decoder_read_bitstream_sv8(d, r, i->is_key_frame);
	else
		mpc_decoder_read_bitstream_sv7(d, r);

	if (d->samples_to_skip < MPC_FRAME_LENGTH + MPC_DECODER_SYNTH_DELAY) {
		mpc_decoder_requantisierung(d);
		mpc_decoder_synthese_filter_float(d, i->buffer, d->channels);
	}

	d->decoded_samples += MPC_FRAME_LENGTH;

    // reconstruct exact filelength
	if (d->decoded_samples - d->samples < MPC_FRAME_LENGTH && d->stream_version == 7) {
		int last_frame_samples = mpc_bits_read(r, 11);
		if (d->decoded_samples == d->samples) {
			if (last_frame_samples == 0) last_frame_samples = MPC_FRAME_LENGTH;
			d->samples += last_frame_samples - MPC_FRAME_LENGTH;
			samples_left += last_frame_samples - MPC_FRAME_LENGTH;
		}
	}

	i->samples = samples_left > MPC_FRAME_LENGTH ? MPC_FRAME_LENGTH : samples_left < 0 ? 0 : (mpc_uint32_t) samples_left;
	i->bits = (mpc_uint32_t) (((r->buff - r_sav.buff) << 3) + r_sav.count - r->count);

	if (d->samples_to_skip) {
		if (i->samples <= d->samples_to_skip) {
			d->samples_to_skip -= i->samples;
			i->samples = 0;
		} else {
			i->samples -= d->samples_to_skip;
			memmove(i->buffer, i->buffer + d->samples_to_skip * d->channels,
					i->samples * d->channels * sizeof (MPC_SAMPLE_FORMAT));
			d->samples_to_skip = 0;
		}
	}
}