#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int stream_version; int samples; scalar_t__ is_true_gapless; scalar_t__ beg_silence; int /*<<< orphan*/  channels; int /*<<< orphan*/  max_band; int /*<<< orphan*/  ms; } ;
typedef  TYPE_1__ mpc_streaminfo ;
struct TYPE_6__ {int stream_version; int samples; scalar_t__ samples_to_skip; int /*<<< orphan*/  channels; int /*<<< orphan*/  max_band; int /*<<< orphan*/  ms; } ;
typedef  TYPE_2__ mpc_decoder ;

/* Variables and functions */
 scalar_t__ MPC_DECODER_SYNTH_DELAY ; 
 int MPC_FRAME_LENGTH ; 

void mpc_decoder_set_streaminfo(mpc_decoder *d, mpc_streaminfo *si)
{
	d->stream_version     = si->stream_version;
	d->ms                 = si->ms;
	d->max_band           = si->max_band;
	d->channels           = si->channels;
	d->samples_to_skip    = MPC_DECODER_SYNTH_DELAY + si->beg_silence;

	if (si->stream_version == 7 && si->is_true_gapless)
		d->samples = ((si->samples + MPC_FRAME_LENGTH - 1) / MPC_FRAME_LENGTH) * MPC_FRAME_LENGTH;
	else
		d->samples = si->samples;
}