#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_4__* audio; } ;
struct TYPE_20__ {TYPE_5__ audio; } ;
typedef  TYPE_7__ sync_stream_t ;
typedef  double int64_t ;
struct TYPE_19__ {double start; double stop; double duration; } ;
struct TYPE_21__ {TYPE_6__ s; int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  TYPE_8__ hb_buffer_t ;
typedef  int /*<<< orphan*/  hb_buffer_list_t ;
struct TYPE_15__ {int codec; int /*<<< orphan*/  mixdown; } ;
struct TYPE_14__ {int samples_per_frame; int samplerate; } ;
struct TYPE_16__ {TYPE_2__ out; TYPE_1__ in; } ;
struct TYPE_17__ {TYPE_3__ config; } ;

/* Variables and functions */
 int HB_ACODEC_PASS_FLAG ; 
 TYPE_8__* hb_buffer_init (int) ; 
 int /*<<< orphan*/  hb_buffer_list_append (int /*<<< orphan*/ *,TYPE_8__*) ; 
 TYPE_8__* hb_buffer_list_clear (int /*<<< orphan*/ *) ; 
 int hb_mixdown_get_discrete_channel_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static hb_buffer_t * CreateSilenceBuf( sync_stream_t * stream,
                                       int64_t dur, int64_t pts )
{
    double             frame_dur, next_pts, duration;
    int                size;
    hb_buffer_list_t   list;
    hb_buffer_t      * buf;

    if (stream->audio.audio->config.out.codec & HB_ACODEC_PASS_FLAG)
    {
        return NULL;
    }
    duration = dur;
    // Although frame size isn't technically important any more, we
    // keep audio buffer durations <= input audio buffer durations.
    frame_dur = (90000. * stream->audio.audio->config.in.samples_per_frame) /
                          stream->audio.audio->config.in.samplerate;
    // Audio mixdown occurs in decoders before sync.
    // So number of channels here is output channel count.
    // But audio samplerate conversion happens in later here in sync.c
    // FilterAudioFrame, so samples_per_frame is still the input sample count.
    size = sizeof(float) * stream->audio.audio->config.in.samples_per_frame *
                           hb_mixdown_get_discrete_channel_count(
                                    stream->audio.audio->config.out.mixdown);

    hb_buffer_list_clear(&list);
    next_pts = pts;
    while (duration >= frame_dur)
    {
        buf = hb_buffer_init(size);
        memset(buf->data, 0, buf->size);
        buf->s.start     = next_pts;
        next_pts        += frame_dur;
        buf->s.stop      = next_pts;
        buf->s.duration  = frame_dur;
        duration        -= frame_dur;
        hb_buffer_list_append(&list, buf);
    }
    if (duration > 0)
    {
        // Make certain size is even multiple of sample size * num channels
        size = (int)(duration * stream->audio.audio->config.in.samplerate /
                     90000) * sizeof(float) *
               hb_mixdown_get_discrete_channel_count(
                                    stream->audio.audio->config.out.mixdown);
        if (size > 0)
        {
            buf = hb_buffer_init(size);
            memset(buf->data, 0, buf->size);
            buf->s.start     = next_pts;
            next_pts        += duration;
            buf->s.stop      = next_pts;
            buf->s.duration  = duration;
            hb_buffer_list_append(&list, buf);
        }
    }
    return hb_buffer_list_clear(&list);
}