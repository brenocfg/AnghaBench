#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_24__ {int err_recognition; TYPE_5__* priv_data; } ;
struct TYPE_23__ {scalar_t__ pts; TYPE_13__** rects; int /*<<< orphan*/  num_rects; scalar_t__ format; int /*<<< orphan*/  end_display_time; scalar_t__ start_display_time; } ;
struct TYPE_19__ {scalar_t__ pts; int object_count; TYPE_1__* objects; int /*<<< orphan*/  palette_id; } ;
struct TYPE_22__ {TYPE_2__ presentation; int /*<<< orphan*/  forced_subs_only; int /*<<< orphan*/  objects; int /*<<< orphan*/  palettes; } ;
struct TYPE_21__ {int /*<<< orphan*/  rle_data_len; scalar_t__ rle; scalar_t__ rle_remaining_len; int /*<<< orphan*/  w; int /*<<< orphan*/  h; } ;
struct TYPE_20__ {int /*<<< orphan*/  clut; } ;
struct TYPE_18__ {int composition_flag; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  id; } ;
struct TYPE_17__ {int nb_colors; void** data; int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/ * linesize; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ PGSSubPalette ;
typedef  TYPE_4__ PGSSubObject ;
typedef  TYPE_5__ PGSSubContext ;
typedef  TYPE_6__ AVSubtitle ;
typedef  TYPE_7__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVPALETTE_SIZE ; 
 int AV_EF_EXPLODE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  AV_SUBTITLE_FLAG_FORCED ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SUBTITLE_BITMAP ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 void* av_mallocz (int) ; 
 TYPE_13__** av_mallocz_array (int,int) ; 
 int /*<<< orphan*/  avsubtitle_free (TYPE_6__*) ; 
 int decode_rle (TYPE_7__*,TYPE_13__*,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_4__* find_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* find_palette (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int display_end_segment(AVCodecContext *avctx, void *data,
                               const uint8_t *buf, int buf_size)
{
    AVSubtitle    *sub = data;
    PGSSubContext *ctx = avctx->priv_data;
    int64_t pts;
    PGSSubPalette *palette;
    int i, ret;

    pts = ctx->presentation.pts != AV_NOPTS_VALUE ? ctx->presentation.pts : sub->pts;
    memset(sub, 0, sizeof(*sub));
    sub->pts = pts;
    ctx->presentation.pts = AV_NOPTS_VALUE;
    sub->start_display_time = 0;
    // There is no explicit end time for PGS subtitles.  The end time
    // is defined by the start of the next sub which may contain no
    // objects (i.e. clears the previous sub)
    sub->end_display_time   = UINT32_MAX;
    sub->format             = 0;

    // Blank if last object_count was 0.
    if (!ctx->presentation.object_count)
        return 1;
    sub->rects = av_mallocz_array(ctx->presentation.object_count, sizeof(*sub->rects));
    if (!sub->rects) {
        return AVERROR(ENOMEM);
    }
    palette = find_palette(ctx->presentation.palette_id, &ctx->palettes);
    if (!palette) {
        // Missing palette.  Should only happen with damaged streams.
        av_log(avctx, AV_LOG_ERROR, "Invalid palette id %d\n",
               ctx->presentation.palette_id);
        avsubtitle_free(sub);
        return AVERROR_INVALIDDATA;
    }
    for (i = 0; i < ctx->presentation.object_count; i++) {
        PGSSubObject *object;

        sub->rects[i]  = av_mallocz(sizeof(*sub->rects[0]));
        if (!sub->rects[i]) {
            avsubtitle_free(sub);
            return AVERROR(ENOMEM);
        }
        sub->num_rects++;
        sub->rects[i]->type = SUBTITLE_BITMAP;

        /* Process bitmap */
        object = find_object(ctx->presentation.objects[i].id, &ctx->objects);
        if (!object) {
            // Missing object.  Should only happen with damaged streams.
            av_log(avctx, AV_LOG_ERROR, "Invalid object id %d\n",
                   ctx->presentation.objects[i].id);
            if (avctx->err_recognition & AV_EF_EXPLODE) {
                avsubtitle_free(sub);
                return AVERROR_INVALIDDATA;
            }
            // Leaves rect empty with 0 width and height.
            continue;
        }
        if (ctx->presentation.objects[i].composition_flag & 0x40)
            sub->rects[i]->flags |= AV_SUBTITLE_FLAG_FORCED;

        sub->rects[i]->x    = ctx->presentation.objects[i].x;
        sub->rects[i]->y    = ctx->presentation.objects[i].y;

        if (object->rle) {
            sub->rects[i]->w    = object->w;
            sub->rects[i]->h    = object->h;

            sub->rects[i]->linesize[0] = object->w;

            if (object->rle_remaining_len) {
                av_log(avctx, AV_LOG_ERROR, "RLE data length %u is %u bytes shorter than expected\n",
                       object->rle_data_len, object->rle_remaining_len);
                if (avctx->err_recognition & AV_EF_EXPLODE) {
                    avsubtitle_free(sub);
                    return AVERROR_INVALIDDATA;
                }
            }
            ret = decode_rle(avctx, sub->rects[i], object->rle, object->rle_data_len);
            if (ret < 0) {
                if ((avctx->err_recognition & AV_EF_EXPLODE) ||
                    ret == AVERROR(ENOMEM)) {
                    avsubtitle_free(sub);
                    return ret;
                }
                sub->rects[i]->w = 0;
                sub->rects[i]->h = 0;
                continue;
            }
        }
        /* Allocate memory for colors */
        sub->rects[i]->nb_colors    = 256;
        sub->rects[i]->data[1] = av_mallocz(AVPALETTE_SIZE);
        if (!sub->rects[i]->data[1]) {
            avsubtitle_free(sub);
            return AVERROR(ENOMEM);
        }

        if (!ctx->forced_subs_only || ctx->presentation.objects[i].composition_flag & 0x40)
        memcpy(sub->rects[i]->data[1], palette->clut, sub->rects[i]->nb_colors * sizeof(uint32_t));

#if FF_API_AVPICTURE
FF_DISABLE_DEPRECATION_WARNINGS
{
        AVSubtitleRect *rect;
        int j;
        rect = sub->rects[i];
        for (j = 0; j < 4; j++) {
            rect->pict.data[j] = rect->data[j];
            rect->pict.linesize[j] = rect->linesize[j];
        }
}
FF_ENABLE_DEPRECATION_WARNINGS
#endif
    }
    return 1;
}