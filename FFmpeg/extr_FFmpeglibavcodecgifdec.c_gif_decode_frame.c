#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int key_frame; int /*<<< orphan*/  pict_type; int /*<<< orphan*/  pkt_duration; int /*<<< orphan*/  pkt_dts; int /*<<< orphan*/  pts; } ;
struct TYPE_19__ {TYPE_1__* priv_data; } ;
struct TYPE_18__ {int size; int /*<<< orphan*/  data; int /*<<< orphan*/  duration; int /*<<< orphan*/  dts; int /*<<< orphan*/  pts; } ;
struct TYPE_17__ {int keyframe; int keyframe_ok; int /*<<< orphan*/  gb; TYPE_6__* frame; int /*<<< orphan*/  idx_line; int /*<<< orphan*/  screen_width; int /*<<< orphan*/  idx_line_size; int /*<<< orphan*/  screen_height; int /*<<< orphan*/  gce_prev_disposal; } ;
typedef  TYPE_1__ GifState ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_P ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GCE_DISPOSAL_NONE ; 
 int /*<<< orphan*/  av_fast_malloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int av_frame_ref (void*,TYPE_6__*) ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_6__*) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int bytestream2_tell (int /*<<< orphan*/ *) ; 
 int ff_get_buffer (TYPE_3__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int ff_reget_buffer (TYPE_3__*,TYPE_6__*) ; 
 int ff_set_dimensions (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gif87a_sig ; 
 int /*<<< orphan*/  gif89a_sig ; 
 int gif_parse_next_image (TYPE_1__*,TYPE_6__*) ; 
 int gif_read_header1 (TYPE_1__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gif_decode_frame(AVCodecContext *avctx, void *data, int *got_frame, AVPacket *avpkt)
{
    GifState *s = avctx->priv_data;
    int ret;

    bytestream2_init(&s->gb, avpkt->data, avpkt->size);

    s->frame->pts     = avpkt->pts;
#if FF_API_PKT_PTS
FF_DISABLE_DEPRECATION_WARNINGS
    s->frame->pkt_pts = avpkt->pts;
FF_ENABLE_DEPRECATION_WARNINGS
#endif
    s->frame->pkt_dts = avpkt->dts;
    s->frame->pkt_duration = avpkt->duration;

    if (avpkt->size >= 6) {
        s->keyframe = memcmp(avpkt->data, gif87a_sig, 6) == 0 ||
                      memcmp(avpkt->data, gif89a_sig, 6) == 0;
    } else {
        s->keyframe = 0;
    }

    if (s->keyframe) {
        s->keyframe_ok = 0;
        s->gce_prev_disposal = GCE_DISPOSAL_NONE;
        if ((ret = gif_read_header1(s)) < 0)
            return ret;

        if ((ret = ff_set_dimensions(avctx, s->screen_width, s->screen_height)) < 0)
            return ret;

        av_frame_unref(s->frame);
        if ((ret = ff_get_buffer(avctx, s->frame, 0)) < 0)
            return ret;

        av_fast_malloc(&s->idx_line, &s->idx_line_size, s->screen_width);
        if (!s->idx_line)
            return AVERROR(ENOMEM);

        s->frame->pict_type = AV_PICTURE_TYPE_I;
        s->frame->key_frame = 1;
        s->keyframe_ok = 1;
    } else {
        if (!s->keyframe_ok) {
            av_log(avctx, AV_LOG_ERROR, "cannot decode frame without keyframe\n");
            return AVERROR_INVALIDDATA;
        }

        if ((ret = ff_reget_buffer(avctx, s->frame)) < 0)
            return ret;

        s->frame->pict_type = AV_PICTURE_TYPE_P;
        s->frame->key_frame = 0;
    }

    ret = gif_parse_next_image(s, s->frame);
    if (ret < 0)
        return ret;

    if ((ret = av_frame_ref(data, s->frame)) < 0)
        return ret;
    *got_frame = 1;

    return bytestream2_tell(&s->gb);
}