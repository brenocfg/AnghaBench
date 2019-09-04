#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_20__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_23__ {scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_1__ svq1_pmv ;
struct TYPE_28__ {scalar_t__ skip_frame; int flags; TYPE_2__* priv_data; } ;
struct TYPE_27__ {scalar_t__ pict_type; int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_26__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_25__ {int frame_code; int width; int height; TYPE_20__* prev; scalar_t__ nonref; int /*<<< orphan*/  gb; int /*<<< orphan*/  hdsp; int /*<<< orphan*/ * pkt_swapped; int /*<<< orphan*/  pkt_swapped_allocated; } ;
struct TYPE_24__ {scalar_t__ width; scalar_t__ height; int /*<<< orphan*/ ** data; } ;
typedef  TYPE_2__ SVQ1Context ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AVDISCARD_ALL ; 
 scalar_t__ AVDISCARD_NONKEY ; 
 scalar_t__ AVDISCARD_NONREF ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AV_CODEC_FLAG_GRAY ; 
 int /*<<< orphan*/  AV_GET_BUFFER_FLAG_REF ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFALIGN (int,int) ; 
 int /*<<< orphan*/  av_fast_padded_malloc (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int av_frame_ref (TYPE_20__*,TYPE_4__*) ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_20__*) ; 
 int /*<<< orphan*/  av_free (TYPE_1__*) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* av_malloc (int) ; 
 int /*<<< orphan*/  ff_dlog (TYPE_5__*,char*,int) ; 
 int ff_get_buffer (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int ff_set_dimensions (TYPE_5__*,int,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int svq1_decode_block_intra (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int svq1_decode_delta_block (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_1__*,int,int,int,int) ; 
 int svq1_decode_frame_header (TYPE_5__*,TYPE_4__*) ; 

__attribute__((used)) static int svq1_decode_frame(AVCodecContext *avctx, void *data,
                             int *got_frame, AVPacket *avpkt)
{
    const uint8_t *buf = avpkt->data;
    int buf_size       = avpkt->size;
    SVQ1Context     *s = avctx->priv_data;
    AVFrame       *cur = data;
    uint8_t *current;
    int result, i, x, y, width, height;
    svq1_pmv *pmv;
    int ret;

    /* initialize bit buffer */
    ret = init_get_bits8(&s->gb, buf, buf_size);
    if (ret < 0)
        return ret;

    /* decode frame header */
    s->frame_code = get_bits(&s->gb, 22);

    if ((s->frame_code & ~0x70) || !(s->frame_code & 0x60))
        return AVERROR_INVALIDDATA;

    /* swap some header bytes (why?) */
    if (s->frame_code != 0x20) {
        uint32_t *src;

        if (buf_size < 9 * 4) {
            av_log(avctx, AV_LOG_ERROR, "Input packet too small\n");
            return AVERROR_INVALIDDATA;
        }

        av_fast_padded_malloc(&s->pkt_swapped,
                              &s->pkt_swapped_allocated,
                              buf_size);
        if (!s->pkt_swapped)
            return AVERROR(ENOMEM);

        memcpy(s->pkt_swapped, buf, buf_size);
        buf = s->pkt_swapped;
        init_get_bits(&s->gb, buf, buf_size * 8);
        skip_bits(&s->gb, 22);

        src = (uint32_t *)(s->pkt_swapped + 4);

        for (i = 0; i < 4; i++)
            src[i] = ((src[i] << 16) | (src[i] >> 16)) ^ src[7 - i];
    }

    result = svq1_decode_frame_header(avctx, cur);
    if (result != 0) {
        ff_dlog(avctx, "Error in svq1_decode_frame_header %i\n", result);
        return result;
    }

    result = ff_set_dimensions(avctx, s->width, s->height);
    if (result < 0)
        return result;

    if ((avctx->skip_frame >= AVDISCARD_NONREF && s->nonref) ||
        (avctx->skip_frame >= AVDISCARD_NONKEY &&
         cur->pict_type != AV_PICTURE_TYPE_I) ||
        avctx->skip_frame >= AVDISCARD_ALL)
        return buf_size;

    result = ff_get_buffer(avctx, cur, s->nonref ? 0 : AV_GET_BUFFER_FLAG_REF);
    if (result < 0)
        return result;

    pmv = av_malloc((FFALIGN(s->width, 16) / 8 + 3) * sizeof(*pmv));
    if (!pmv)
        return AVERROR(ENOMEM);

    /* decode y, u and v components */
    for (i = 0; i < 3; i++) {
        int linesize = cur->linesize[i];
        if (i == 0) {
            width    = FFALIGN(s->width,  16);
            height   = FFALIGN(s->height, 16);
        } else {
            if (avctx->flags & AV_CODEC_FLAG_GRAY)
                break;
            width    = FFALIGN(s->width  / 4, 16);
            height   = FFALIGN(s->height / 4, 16);
        }

        current = cur->data[i];

        if (cur->pict_type == AV_PICTURE_TYPE_I) {
            /* keyframe */
            for (y = 0; y < height; y += 16) {
                for (x = 0; x < width; x += 16) {
                    result = svq1_decode_block_intra(&s->gb, &current[x],
                                                     linesize);
                    if (result) {
                        av_log(avctx, AV_LOG_ERROR,
                               "Error in svq1_decode_block %i (keyframe)\n",
                               result);
                        goto err;
                    }
                }
                current += 16 * linesize;
            }
        } else {
            /* delta frame */
            uint8_t *previous = s->prev->data[i];
            if (!previous ||
                s->prev->width != s->width || s->prev->height != s->height) {
                av_log(avctx, AV_LOG_ERROR, "Missing reference frame.\n");
                result = AVERROR_INVALIDDATA;
                goto err;
            }

            memset(pmv, 0, ((width / 8) + 3) * sizeof(svq1_pmv));

            for (y = 0; y < height; y += 16) {
                for (x = 0; x < width; x += 16) {
                    result = svq1_decode_delta_block(avctx, &s->hdsp,
                                                     &s->gb, &current[x],
                                                     previous, linesize,
                                                     pmv, x, y, width, height);
                    if (result != 0) {
                        ff_dlog(avctx,
                                "Error in svq1_decode_delta_block %i\n",
                                result);
                        goto err;
                    }
                }

                pmv[0].x     =
                    pmv[0].y = 0;

                current += 16 * linesize;
            }
        }
    }

    if (!s->nonref) {
        av_frame_unref(s->prev);
        result = av_frame_ref(s->prev, cur);
        if (result < 0)
            goto err;
    }

    *got_frame = 1;
    result     = buf_size;

err:
    av_free(pmv);
    return result;
}