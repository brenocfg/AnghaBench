#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_14__ {int type; int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  dst; } ;
struct TYPE_13__ {int /*<<< orphan*/  format; int /*<<< orphan*/  channels; int /*<<< orphan*/  nb_samples; int /*<<< orphan*/  extended_data; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  linesize; scalar_t__ data; } ;
typedef  TYPE_1__ AVFrame ;
typedef  TYPE_2__ AVFilterLink ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AVMEDIA_TYPE_AUDIO 129 
#define  AVMEDIA_TYPE_VIDEO 128 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int av_frame_copy_props (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_1__**) ; 
 scalar_t__ av_frame_is_writable (TYPE_1__*) ; 
 int /*<<< orphan*/  av_image_copy (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_samples_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ff_get_audio_buffer (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* ff_get_video_buffer (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ff_inlink_make_frame_writable(AVFilterLink *link, AVFrame **rframe)
{
    AVFrame *frame = *rframe;
    AVFrame *out;
    int ret;

    if (av_frame_is_writable(frame))
        return 0;
    av_log(link->dst, AV_LOG_DEBUG, "Copying data in avfilter.\n");

    switch (link->type) {
    case AVMEDIA_TYPE_VIDEO:
        out = ff_get_video_buffer(link, link->w, link->h);
        break;
    case AVMEDIA_TYPE_AUDIO:
        out = ff_get_audio_buffer(link, frame->nb_samples);
        break;
    default:
        return AVERROR(EINVAL);
    }
    if (!out)
        return AVERROR(ENOMEM);

    ret = av_frame_copy_props(out, frame);
    if (ret < 0) {
        av_frame_free(&out);
        return ret;
    }

    switch (link->type) {
    case AVMEDIA_TYPE_VIDEO:
        av_image_copy(out->data, out->linesize, (const uint8_t **)frame->data, frame->linesize,
                      frame->format, frame->width, frame->height);
        break;
    case AVMEDIA_TYPE_AUDIO:
        av_samples_copy(out->extended_data, frame->extended_data,
                        0, 0, frame->nb_samples,
                        frame->channels,
                        frame->format);
        break;
    default:
        av_assert0(!"reached");
    }

    av_frame_free(&frame);
    *rframe = out;
    return 0;
}