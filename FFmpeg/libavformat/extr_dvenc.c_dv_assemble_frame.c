#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_12__ {int frame_size; } ;
struct TYPE_11__ {TYPE_1__* codecpar; } ;
struct TYPE_10__ {int has_video; int n_ast; int has_audio; TYPE_6__* sys; int /*<<< orphan*/  frames; int /*<<< orphan*/ * audio_data; TYPE_3__** ast; int /*<<< orphan*/ * frame_buf; } ;
struct TYPE_9__ {int codec_type; int /*<<< orphan*/  sample_rate; } ;
typedef  TYPE_2__ DVMuxContext ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AVMEDIA_TYPE_AUDIO 129 
#define  AVMEDIA_TYPE_VIDEO 128 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOSYS ; 
 int MAX_AUDIO_FRAME_SIZE ; 
 int /*<<< orphan*/  av_fifo_drain (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_fifo_generic_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int av_fifo_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,...) ; 
 int dv_audio_frame_size (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dv_inject_audio (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dv_inject_metadata (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dv_assemble_frame(AVFormatContext *s,
                             DVMuxContext *c, AVStream* st,
                             uint8_t* data, int data_size, uint8_t** frame)
{
    int i, reqasize;

    *frame = &c->frame_buf[0];

    switch (st->codecpar->codec_type) {
    case AVMEDIA_TYPE_VIDEO:
        /* FIXME: we have to have more sensible approach than this one */
        if (c->has_video)
            av_log(s, AV_LOG_ERROR, "Can't process DV frame #%d. Insufficient audio data or severe sync problem.\n", c->frames);
        if (data_size != c->sys->frame_size) {
            av_log(s, AV_LOG_ERROR, "Unexpected frame size, %d != %d\n",
                   data_size, c->sys->frame_size);
            return AVERROR(ENOSYS);
        }

        memcpy(*frame, data, c->sys->frame_size);
        c->has_video = 1;
        break;
    case AVMEDIA_TYPE_AUDIO:
        for (i = 0; i < c->n_ast && st != c->ast[i]; i++);

          /* FIXME: we have to have more sensible approach than this one */
        if (av_fifo_size(c->audio_data[i]) + data_size >= 100*MAX_AUDIO_FRAME_SIZE)
            av_log(s, AV_LOG_ERROR, "Can't process DV frame #%d. Insufficient video data or severe sync problem.\n", c->frames);
        av_fifo_generic_write(c->audio_data[i], data, data_size, NULL);

        reqasize = 4 * dv_audio_frame_size(c->sys, c->frames, st->codecpar->sample_rate);

        /* Let us see if we've got enough audio for one DV frame. */
        c->has_audio |= ((reqasize <= av_fifo_size(c->audio_data[i])) << i);

        break;
    default:
        break;
    }

    /* Let us see if we have enough data to construct one DV frame. */
    if (c->has_video == 1 && c->has_audio + 1 == 1 << c->n_ast) {
        dv_inject_metadata(c, *frame);
        c->has_audio = 0;
        for (i=0; i < c->n_ast; i++) {
            dv_inject_audio(c, i, *frame);
            reqasize = 4 * dv_audio_frame_size(c->sys, c->frames, c->ast[i]->codecpar->sample_rate);
            av_fifo_drain(c->audio_data[i], reqasize);
            c->has_audio |= ((reqasize <= av_fifo_size(c->audio_data[i])) << i);
        }

        c->has_video = 0;

        c->frames++;

        return c->sys->frame_size;
    }

    return 0;
}