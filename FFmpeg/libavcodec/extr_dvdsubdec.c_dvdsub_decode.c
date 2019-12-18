#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ppm_name ;
struct TYPE_18__ {TYPE_2__* priv_data; } ;
struct TYPE_17__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_16__ {TYPE_1__** rects; int /*<<< orphan*/  end_display_time; int /*<<< orphan*/  start_display_time; } ;
struct TYPE_15__ {int buf_size; int /*<<< orphan*/  sub_id; scalar_t__ forced_subs_only; int /*<<< orphan*/ * buf; } ;
struct TYPE_14__ {int flags; scalar_t__* data; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
typedef  TYPE_2__ DVDSubContext ;
typedef  TYPE_3__ AVSubtitle ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_SUBTITLE_FLAG_FORCED ; 
 int /*<<< orphan*/  EAGAIN ; 
 int append_to_cached_buf (TYPE_5__*,int /*<<< orphan*/  const*,int) ; 
 int decode_dvd_subtitles (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ff_dlog (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ find_smallest_bounding_rectangle (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ppm_save (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_rects (TYPE_3__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dvdsub_decode(AVCodecContext *avctx,
                         void *data, int *data_size,
                         AVPacket *avpkt)
{
    DVDSubContext *ctx = avctx->priv_data;
    const uint8_t *buf = avpkt->data;
    int buf_size = avpkt->size;
    AVSubtitle *sub = data;
    int appended = 0;
    int is_menu;

    if (ctx->buf_size) {
        int ret = append_to_cached_buf(avctx, buf, buf_size);
        if (ret < 0) {
            *data_size = 0;
            return ret;
        }
        buf = ctx->buf;
        buf_size = ctx->buf_size;
        appended = 1;
    }

    is_menu = decode_dvd_subtitles(ctx, sub, buf, buf_size);
    if (is_menu == AVERROR(EAGAIN)) {
        *data_size = 0;
        return appended ? 0 : append_to_cached_buf(avctx, buf, buf_size);
    }

    if (is_menu < 0) {
        ctx->buf_size = 0;
    no_subtitle:
        reset_rects(sub);
        *data_size = 0;

        return buf_size;
    }
    if (!is_menu && find_smallest_bounding_rectangle(ctx, sub) == 0)
        goto no_subtitle;

    if (ctx->forced_subs_only && !(sub->rects[0]->flags & AV_SUBTITLE_FLAG_FORCED))
        goto no_subtitle;

#if defined(DEBUG)
    {
    char ppm_name[32];

    snprintf(ppm_name, sizeof(ppm_name), "/tmp/%05d.ppm", ctx->sub_id++);
    ff_dlog(NULL, "start=%d ms end =%d ms\n",
            sub->start_display_time,
            sub->end_display_time);
    ppm_save(ppm_name, sub->rects[0]->data[0],
             sub->rects[0]->w, sub->rects[0]->h, (uint32_t*) sub->rects[0]->data[1]);
    }
#endif

    ctx->buf_size = 0;
    *data_size = 1;
    return buf_size;
}