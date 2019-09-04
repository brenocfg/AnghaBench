#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
struct vpx_image {int d_w; int w; int d_h; int h; int* stride; int /*<<< orphan*/ ** planes; int /*<<< orphan*/  bit_depth; int /*<<< orphan*/  fmt; } ;
struct TYPE_15__ {int has_alpha_channel; int /*<<< orphan*/  decoder_alpha; int /*<<< orphan*/  decoder; } ;
typedef  TYPE_1__ VPxContext ;
struct TYPE_18__ {int width; int height; int /*<<< orphan*/  pix_fmt; TYPE_1__* priv_data; } ;
struct TYPE_17__ {int /*<<< orphan*/  linesize; int /*<<< orphan*/  data; } ;
struct TYPE_16__ {int size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  AV_PKT_DATA_MATROSKA_BLOCKADDITIONAL ; 
 int AV_RB64 (int /*<<< orphan*/ *) ; 
 size_t VPX_PLANE_U ; 
 size_t VPX_PLANE_V ; 
 size_t VPX_PLANE_Y ; 
 int /*<<< orphan*/  av_image_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/ * av_packet_get_side_data (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int decode_frame (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int ff_set_dimensions (TYPE_4__*,int,int) ; 
 int set_pix_fmt (TYPE_4__*,struct vpx_image*,int) ; 
 struct vpx_image* vpx_codec_get_frame (int /*<<< orphan*/ *,void const**) ; 
 int /*<<< orphan*/  vpx_codec_vp9_dx_algo ; 
 int vpx_init (TYPE_4__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int vpx_decode(AVCodecContext *avctx,
                      void *data, int *got_frame, AVPacket *avpkt)
{
    VPxContext *ctx = avctx->priv_data;
    AVFrame *picture = data;
    const void *iter = NULL;
    const void *iter_alpha = NULL;
    struct vpx_image *img, *img_alpha;
    int ret;
    uint8_t *side_data = NULL;
    int side_data_size = 0;

    ret = decode_frame(avctx, &ctx->decoder, avpkt->data, avpkt->size);
    if (ret)
        return ret;

    side_data = av_packet_get_side_data(avpkt,
                                        AV_PKT_DATA_MATROSKA_BLOCKADDITIONAL,
                                        &side_data_size);
    if (side_data_size > 1) {
        const uint64_t additional_id = AV_RB64(side_data);
        side_data += 8;
        side_data_size -= 8;
        if (additional_id == 1) {  // 1 stands for alpha channel data.
            if (!ctx->has_alpha_channel) {
                ctx->has_alpha_channel = 1;
                ret = vpx_init(avctx,
#if CONFIG_LIBVPX_VP8_DECODER && CONFIG_LIBVPX_VP9_DECODER
                               (avctx->codec_id == AV_CODEC_ID_VP8) ?
                               &vpx_codec_vp8_dx_algo : &vpx_codec_vp9_dx_algo,
#elif CONFIG_LIBVPX_VP8_DECODER
                               &vpx_codec_vp8_dx_algo,
#else
                               &vpx_codec_vp9_dx_algo,
#endif
                               1);
                if (ret)
                    return ret;
            }
            ret = decode_frame(avctx, &ctx->decoder_alpha, side_data,
                               side_data_size);
            if (ret)
                return ret;
        }
    }

    if ((img = vpx_codec_get_frame(&ctx->decoder, &iter)) &&
        (!ctx->has_alpha_channel ||
         (img_alpha = vpx_codec_get_frame(&ctx->decoder_alpha, &iter_alpha)))) {
        uint8_t *planes[4];
        int linesizes[4];

        if (img->d_w > img->w || img->d_h > img->h) {
            av_log(avctx, AV_LOG_ERROR, "Display dimensions %dx%d exceed storage %dx%d\n",
                   img->d_w, img->d_h, img->w, img->h);
            return AVERROR_EXTERNAL;
        }

        if ((ret = set_pix_fmt(avctx, img, ctx->has_alpha_channel)) < 0) {
            av_log(avctx, AV_LOG_ERROR, "Unsupported output colorspace (%d) / bit_depth (%d)\n",
                   img->fmt, img->bit_depth);
            return ret;
        }

        if ((int) img->d_w != avctx->width || (int) img->d_h != avctx->height) {
            av_log(avctx, AV_LOG_INFO, "dimension change! %dx%d -> %dx%d\n",
                   avctx->width, avctx->height, img->d_w, img->d_h);
            ret = ff_set_dimensions(avctx, img->d_w, img->d_h);
            if (ret < 0)
                return ret;
        }
        if ((ret = ff_get_buffer(avctx, picture, 0)) < 0)
            return ret;

        planes[0] = img->planes[VPX_PLANE_Y];
        planes[1] = img->planes[VPX_PLANE_U];
        planes[2] = img->planes[VPX_PLANE_V];
        planes[3] =
            ctx->has_alpha_channel ? img_alpha->planes[VPX_PLANE_Y] : NULL;
        linesizes[0] = img->stride[VPX_PLANE_Y];
        linesizes[1] = img->stride[VPX_PLANE_U];
        linesizes[2] = img->stride[VPX_PLANE_V];
        linesizes[3] =
            ctx->has_alpha_channel ? img_alpha->stride[VPX_PLANE_Y] : 0;
        av_image_copy(picture->data, picture->linesize, (const uint8_t**)planes,
                      linesizes, avctx->pix_fmt, img->d_w, img->d_h);
        *got_frame           = 1;
    }
    return avpkt->size;
}