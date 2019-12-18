#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_15__ {double gain_factor; int /*<<< orphan*/ * resample; TYPE_7__* audio; } ;
struct TYPE_17__ {scalar_t__ next_pts; TYPE_3__ audio; } ;
typedef  TYPE_5__ sync_stream_t ;
struct TYPE_16__ {scalar_t__ duration; scalar_t__ stop; scalar_t__ start; int /*<<< orphan*/  frametype; int /*<<< orphan*/  type; } ;
struct TYPE_18__ {int size; TYPE_4__ s; scalar_t__ data; } ;
typedef  TYPE_6__ hb_buffer_t ;
struct TYPE_13__ {int codec; double gain; int /*<<< orphan*/  mixdown; } ;
struct TYPE_14__ {TYPE_1__ out; } ;
struct TYPE_19__ {TYPE_2__ config; } ;
typedef  TYPE_7__ hb_audio_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_BUF ; 
 int HB_ACODEC_PASS_FLAG ; 
 int /*<<< orphan*/  HB_FRAME_AUDIO ; 
 double MAX (double,double) ; 
 double MIN (double,double) ; 
 TYPE_6__* hb_audio_resample (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int) ; 
 int /*<<< orphan*/  hb_buffer_close (TYPE_6__**) ; 
 int hb_mixdown_get_discrete_channel_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static hb_buffer_t * FilterAudioFrame( sync_stream_t * stream,
                                       hb_buffer_t *buf )
{
    hb_audio_t * audio = stream->audio.audio;

    // Can't count of buf->s.stop - buf->s.start for accurate duration
    // due to integer rounding, so use buf->s.duration when it is set
    // (which should be always if I didn't miss anything)
    if (buf->s.duration <= 0)
    {
        buf->s.duration = buf->s.stop - buf->s.start;
    }

    if (!(audio->config.out.codec & HB_ACODEC_PASS_FLAG))
    {
        // TODO: this should all be replaced by an audio filter chain.

        // Audio is not passthru.  Check if we need to modify the audio
        // in any way.
        if (stream->audio.resample != NULL)
        {
            /* do sample rate conversion */
            hb_buffer_t * out;
            int           nsamples, sample_size;

            sample_size = hb_mixdown_get_discrete_channel_count(
                            audio->config.out.mixdown ) * sizeof( float );

            nsamples  = buf->size / sample_size;
            out = hb_audio_resample(stream->audio.resample,
                                    (const uint8_t **)&buf->data,
                                    nsamples);
            hb_buffer_close(&buf);
            if (out == NULL)
            {
                return NULL;
            }
            out->s.start = stream->next_pts;
            out->s.stop  = stream->next_pts + out->s.duration;
            buf = out;
        }
        if (audio->config.out.gain > 0.0)
        {
            int count, ii;

            count  = buf->size / sizeof(float);
            for ( ii = 0; ii < count; ii++ )
            {
                double sample;

                sample = (double)*(((float*)buf->data)+ii);
                sample *= stream->audio.gain_factor;
                if (sample > 0)
                    sample = MIN(sample, 1.0);
                else
                    sample = MAX(sample, -1.0);
                *(((float*)buf->data)+ii) = sample;
            }
        }
        else if( audio->config.out.gain < 0.0 )
        {
            int count, ii;

            count  = buf->size / sizeof(float);
            for ( ii = 0; ii < count; ii++ )
            {
                double sample;

                sample = (double)*(((float*)buf->data)+ii);
                sample *= stream->audio.gain_factor;
                *(((float*)buf->data)+ii) = sample;
            }
        }
    }

    buf->s.type = AUDIO_BUF;
    buf->s.frametype = HB_FRAME_AUDIO;

    return buf;
}