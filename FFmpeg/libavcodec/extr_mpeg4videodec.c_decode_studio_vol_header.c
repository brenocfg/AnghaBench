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
struct TYPE_11__ {void* den; void* num; } ;
struct TYPE_12__ {int bits_per_raw_sample; TYPE_3__ sample_aspect_ratio; int /*<<< orphan*/  pix_fmt; } ;
struct TYPE_9__ {scalar_t__ chroma_format; int width; int height; int context_reinit; size_t aspect_ratio_info; void* mpeg_quant; void* low_delay; TYPE_6__* avctx; } ;
struct TYPE_10__ {void* shape; void* rgb; TYPE_1__ m; } ;
typedef  TYPE_1__ MpegEncContext ;
typedef  TYPE_2__ Mpeg4DecContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PIX_FMT_GBRP10 ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUV422P10 ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUV444P10 ; 
 void* BIN_ONLY_SHAPE ; 
 scalar_t__ CHROMA_422 ; 
 size_t FF_ASPECT_EXTENDED ; 
 void* RECT_SHAPE ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_6__*,char*,int) ; 
 int /*<<< orphan*/  check_marker (TYPE_6__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  extension_and_user_data (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 TYPE_3__* ff_h263_pixel_aspect ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next_start_code_studio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_studio_vol_header(Mpeg4DecContext *ctx, GetBitContext *gb)
{
    MpegEncContext *s = &ctx->m;
    int width, height;
    int bits_per_raw_sample;

            // random_accessible_vol and video_object_type_indication have already
            // been read by the caller decode_vol_header()
            skip_bits(gb, 4); /* video_object_layer_verid */
            ctx->shape = get_bits(gb, 2); /* video_object_layer_shape */
            skip_bits(gb, 4); /* video_object_layer_shape_extension */
            skip_bits1(gb); /* progressive_sequence */
            if (ctx->shape != BIN_ONLY_SHAPE) {
                ctx->rgb = get_bits1(gb); /* rgb_components */
                s->chroma_format = get_bits(gb, 2); /* chroma_format */
                if (!s->chroma_format) {
                    av_log(s->avctx, AV_LOG_ERROR, "illegal chroma format\n");
                    return AVERROR_INVALIDDATA;
                }

                bits_per_raw_sample = get_bits(gb, 4); /* bit_depth */
                if (bits_per_raw_sample == 10) {
                    if (ctx->rgb) {
                        s->avctx->pix_fmt = AV_PIX_FMT_GBRP10;
                    }
                    else {
                        s->avctx->pix_fmt = s->chroma_format == CHROMA_422 ? AV_PIX_FMT_YUV422P10 : AV_PIX_FMT_YUV444P10;
                    }
                }
                else {
                    avpriv_request_sample(s->avctx, "MPEG-4 Studio profile bit-depth %u", bits_per_raw_sample);
                    return AVERROR_PATCHWELCOME;
                }
                s->avctx->bits_per_raw_sample = bits_per_raw_sample;
            }
            if (ctx->shape == RECT_SHAPE) {
                check_marker(s->avctx, gb, "before video_object_layer_width");
                width = get_bits(gb, 14); /* video_object_layer_width */
                check_marker(s->avctx, gb, "before video_object_layer_height");
                height = get_bits(gb, 14); /* video_object_layer_height */
                check_marker(s->avctx, gb, "after video_object_layer_height");

                /* Do the same check as non-studio profile */
                if (width && height) {
                    if (s->width && s->height &&
                        (s->width != width || s->height != height))
                        s->context_reinit = 1;
                    s->width  = width;
                    s->height = height;
                }
            }
            s->aspect_ratio_info = get_bits(gb, 4);
            if (s->aspect_ratio_info == FF_ASPECT_EXTENDED) {
                s->avctx->sample_aspect_ratio.num = get_bits(gb, 8);  // par_width
                s->avctx->sample_aspect_ratio.den = get_bits(gb, 8);  // par_height
            } else {
                s->avctx->sample_aspect_ratio = ff_h263_pixel_aspect[s->aspect_ratio_info];
            }
            skip_bits(gb, 4); /* frame_rate_code */
            skip_bits(gb, 15); /* first_half_bit_rate */
            check_marker(s->avctx, gb, "after first_half_bit_rate");
            skip_bits(gb, 15); /* latter_half_bit_rate */
            check_marker(s->avctx, gb, "after latter_half_bit_rate");
            skip_bits(gb, 15); /* first_half_vbv_buffer_size */
            check_marker(s->avctx, gb, "after first_half_vbv_buffer_size");
            skip_bits(gb, 3); /* latter_half_vbv_buffer_size */
            skip_bits(gb, 11); /* first_half_vbv_buffer_size */
            check_marker(s->avctx, gb, "after first_half_vbv_buffer_size");
            skip_bits(gb, 15); /* latter_half_vbv_occupancy */
            check_marker(s->avctx, gb, "after latter_half_vbv_occupancy");
            s->low_delay = get_bits1(gb);
            s->mpeg_quant = get_bits1(gb); /* mpeg2_stream */

            next_start_code_studio(gb);
            extension_and_user_data(s, gb, 2);

    return 0;
}