#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_15__ {int format; int nb_extended_buf; TYPE_2__** extended_buf; int /*<<< orphan*/ ** extended_data; TYPE_1__** buf; int /*<<< orphan*/ ** data; int /*<<< orphan*/ * linesize; int /*<<< orphan*/  channels; int /*<<< orphan*/  nb_samples; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_14__ {int flags; } ;
struct TYPE_13__ {int type; int format; int planes; int /*<<< orphan*/ * pools; int /*<<< orphan*/ * linesize; int /*<<< orphan*/  channels; int /*<<< orphan*/  nb_samples; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_12__ {int /*<<< orphan*/ * data; } ;
struct TYPE_11__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_3__ FFFramePool ;
typedef  TYPE_4__ AVPixFmtDescriptor ;
typedef  TYPE_5__ AVFrame ;

/* Variables and functions */
#define  AVMEDIA_TYPE_AUDIO 129 
#define  AVMEDIA_TYPE_VIDEO 128 
 int AV_NUM_DATA_POINTERS ; 
 int AV_PIX_FMT_BGR8 ; 
 int AV_PIX_FMT_FLAG_PAL ; 
 int AV_PIX_FMT_PAL8 ; 
 int FFMIN (int,int) ; 
 int FF_PSEUDOPAL ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 void* av_buffer_pool_get (int /*<<< orphan*/ ) ; 
 TYPE_5__* av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (TYPE_5__**) ; 
 void* av_mallocz_array (int,int) ; 
 TYPE_4__* av_pix_fmt_desc_get (int) ; 
 int /*<<< orphan*/  avpriv_set_systematic_pal2 (int /*<<< orphan*/ *,int) ; 

AVFrame *ff_frame_pool_get(FFFramePool *pool)
{
    int i;
    AVFrame *frame;
    const AVPixFmtDescriptor *desc;

    frame = av_frame_alloc();
    if (!frame) {
        return NULL;
    }

    switch(pool->type) {
    case AVMEDIA_TYPE_VIDEO:
        desc = av_pix_fmt_desc_get(pool->format);
        if (!desc) {
            goto fail;
        }

        frame->width = pool->width;
        frame->height = pool->height;
        frame->format = pool->format;

        for (i = 0; i < 4; i++) {
            frame->linesize[i] = pool->linesize[i];
            if (!pool->pools[i])
                break;

            frame->buf[i] = av_buffer_pool_get(pool->pools[i]);
            if (!frame->buf[i])
                goto fail;

            frame->data[i] = frame->buf[i]->data;
        }

        if (desc->flags & AV_PIX_FMT_FLAG_PAL ||
            desc->flags & FF_PSEUDOPAL) {
            enum AVPixelFormat format =
                pool->format == AV_PIX_FMT_PAL8 ? AV_PIX_FMT_BGR8 : pool->format;

            av_assert0(frame->data[1] != NULL);
            if (avpriv_set_systematic_pal2((uint32_t *)frame->data[1], format) < 0)
                goto fail;
        }

        frame->extended_data = frame->data;
        break;
    case AVMEDIA_TYPE_AUDIO:
        frame->nb_samples = pool->nb_samples;
        frame->channels = pool->channels;
        frame->format = pool->format;
        frame->linesize[0] = pool->linesize[0];

        if (pool->planes > AV_NUM_DATA_POINTERS) {
            frame->extended_data = av_mallocz_array(pool->planes,
                                                    sizeof(*frame->extended_data));
            frame->nb_extended_buf = pool->planes - AV_NUM_DATA_POINTERS;
            frame->extended_buf = av_mallocz_array(frame->nb_extended_buf,
                                                   sizeof(*frame->extended_buf));
            if (!frame->extended_data || !frame->extended_buf)
                goto fail;
        } else {
            frame->extended_data = frame->data;
            av_assert0(frame->nb_extended_buf == 0);
        }

        for (i = 0; i < FFMIN(pool->planes, AV_NUM_DATA_POINTERS); i++) {
            frame->buf[i] = av_buffer_pool_get(pool->pools[0]);
            if (!frame->buf[i])
                goto fail;
            frame->extended_data[i] = frame->data[i] = frame->buf[i]->data;
        }
        for (i = 0; i < frame->nb_extended_buf; i++) {
            frame->extended_buf[i] = av_buffer_pool_get(pool->pools[0]);
            if (!frame->extended_buf[i])
                goto fail;
            frame->extended_data[i + AV_NUM_DATA_POINTERS] = frame->extended_buf[i]->data;
        }

        break;
    default:
        av_assert0(0);
    }

    return frame;
fail:
    av_frame_free(&frame);
    return NULL;
}