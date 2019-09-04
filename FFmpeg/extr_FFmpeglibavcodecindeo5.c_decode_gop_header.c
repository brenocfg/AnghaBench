#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_2__* bands; } ;
struct TYPE_10__ {int luma_bands; int chroma_bands; int pic_height; int pic_width; int chroma_height; int chroma_width; int tile_height; int tile_width; } ;
struct TYPE_12__ {int gop_flags; int gop_hdr_size; int is_scalable; int /*<<< orphan*/  gb; TYPE_6__* planes; TYPE_1__ pic_conf; scalar_t__ gop_invalid; int /*<<< orphan*/  lock_word; } ;
struct TYPE_11__ {int is_halfpel; int mb_size; int blk_size; scalar_t__ inv_transform; int transform_size; int is_2d_trans; void* dc_transform; void* scan; int /*<<< orphan*/ * inter_scale; int /*<<< orphan*/ * intra_scale; int /*<<< orphan*/ * inter_base; int /*<<< orphan*/ * intra_base; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_1__ IVIPicConfig ;
typedef  TYPE_2__ IVIBandDesc ;
typedef  TYPE_3__ IVI45DecContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int IVI5_IS_PROTECTED ; 
 int IVI5_PIC_SIZE_ESC ; 
 int /*<<< orphan*/  align_get_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ff_ivi_col_slant8 ; 
 void* ff_ivi_dc_col_slant ; 
 void* ff_ivi_dc_row_slant ; 
 void* ff_ivi_dc_slant_2d ; 
 void* ff_ivi_direct_scan_4x4 ; 
 void* ff_ivi_horizontal_scan_8x8 ; 
 int ff_ivi_init_planes (int /*<<< orphan*/ *,TYPE_6__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int ff_ivi_init_tiles (TYPE_6__*,int,int) ; 
 scalar_t__ ff_ivi_inverse_slant_4x4 ; 
 scalar_t__ ff_ivi_inverse_slant_8x8 ; 
 void* ff_ivi_put_dc_pixel_8x8 ; 
 scalar_t__ ff_ivi_put_pixels_8x8 ; 
 scalar_t__ ff_ivi_row_slant8 ; 
 void* ff_ivi_vertical_scan_8x8 ; 
 void* ff_zigzag_direct ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_bits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ivi5_base_quant_4x4_inter ; 
 int /*<<< orphan*/ * ivi5_base_quant_4x4_intra ; 
 int /*<<< orphan*/ ** ivi5_base_quant_8x8_inter ; 
 int /*<<< orphan*/ ** ivi5_base_quant_8x8_intra ; 
 int* ivi5_common_pic_sizes ; 
 int /*<<< orphan*/ * ivi5_scale_quant_4x4_inter ; 
 int /*<<< orphan*/ * ivi5_scale_quant_4x4_intra ; 
 int /*<<< orphan*/ ** ivi5_scale_quant_8x8_inter ; 
 int /*<<< orphan*/ ** ivi5_scale_quant_8x8_intra ; 
 scalar_t__ ivi_pic_config_cmp (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int decode_gop_header(IVI45DecContext *ctx, AVCodecContext *avctx)
{
    int             result, i, p, tile_size, pic_size_indx, mb_size, blk_size, is_scalable;
    int             quant_mat, blk_size_changed = 0;
    IVIBandDesc     *band, *band1, *band2;
    IVIPicConfig    pic_conf;

    ctx->gop_flags = get_bits(&ctx->gb, 8);

    ctx->gop_hdr_size = (ctx->gop_flags & 1) ? get_bits(&ctx->gb, 16) : 0;

    if (ctx->gop_flags & IVI5_IS_PROTECTED)
        ctx->lock_word = get_bits_long(&ctx->gb, 32);

    tile_size = (ctx->gop_flags & 0x40) ? 64 << get_bits(&ctx->gb, 2) : 0;
    if (tile_size > 256) {
        av_log(avctx, AV_LOG_ERROR, "Invalid tile size: %d\n", tile_size);
        return AVERROR_INVALIDDATA;
    }

    /* decode number of wavelet bands */
    /* num_levels * 3 + 1 */
    pic_conf.luma_bands   = get_bits(&ctx->gb, 2) * 3 + 1;
    pic_conf.chroma_bands = get_bits1(&ctx->gb)   * 3 + 1;
    is_scalable = pic_conf.luma_bands != 1 || pic_conf.chroma_bands != 1;
    if (is_scalable && (pic_conf.luma_bands != 4 || pic_conf.chroma_bands != 1)) {
        av_log(avctx, AV_LOG_ERROR, "Scalability: unsupported subdivision! Luma bands: %d, chroma bands: %d\n",
               pic_conf.luma_bands, pic_conf.chroma_bands);
        return AVERROR_INVALIDDATA;
    }

    pic_size_indx = get_bits(&ctx->gb, 4);
    if (pic_size_indx == IVI5_PIC_SIZE_ESC) {
        pic_conf.pic_height = get_bits(&ctx->gb, 13);
        pic_conf.pic_width  = get_bits(&ctx->gb, 13);
    } else {
        pic_conf.pic_height = ivi5_common_pic_sizes[pic_size_indx * 2 + 1] << 2;
        pic_conf.pic_width  = ivi5_common_pic_sizes[pic_size_indx * 2    ] << 2;
    }

    if (ctx->gop_flags & 2) {
        avpriv_report_missing_feature(avctx, "YV12 picture format");
        return AVERROR_PATCHWELCOME;
    }

    pic_conf.chroma_height = (pic_conf.pic_height + 3) >> 2;
    pic_conf.chroma_width  = (pic_conf.pic_width  + 3) >> 2;

    if (!tile_size) {
        pic_conf.tile_height = pic_conf.pic_height;
        pic_conf.tile_width  = pic_conf.pic_width;
    } else {
        pic_conf.tile_height = pic_conf.tile_width = tile_size;
    }

    /* check if picture layout was changed and reallocate buffers */
    if (ivi_pic_config_cmp(&pic_conf, &ctx->pic_conf) || ctx->gop_invalid) {
        result = ff_ivi_init_planes(avctx, ctx->planes, &pic_conf, 0);
        if (result < 0) {
            av_log(avctx, AV_LOG_ERROR, "Couldn't reallocate color planes!\n");
            return result;
        }
        ctx->pic_conf = pic_conf;
        ctx->is_scalable = is_scalable;
        blk_size_changed = 1; /* force reallocation of the internal structures */
    }

    for (p = 0; p <= 1; p++) {
        for (i = 0; i < (!p ? pic_conf.luma_bands : pic_conf.chroma_bands); i++) {
            band = &ctx->planes[p].bands[i];

            band->is_halfpel = get_bits1(&ctx->gb);

            mb_size  = get_bits1(&ctx->gb);
            blk_size = 8 >> get_bits1(&ctx->gb);
            mb_size  = blk_size << !mb_size;

            if (p==0 && blk_size==4) {
                av_log(avctx, AV_LOG_ERROR, "4x4 luma blocks are unsupported!\n");
                return AVERROR_PATCHWELCOME;
            }

            blk_size_changed = mb_size != band->mb_size || blk_size != band->blk_size;
            if (blk_size_changed) {
                band->mb_size  = mb_size;
                band->blk_size = blk_size;
            }

            if (get_bits1(&ctx->gb)) {
                avpriv_report_missing_feature(avctx, "Extended transform info");
                return AVERROR_PATCHWELCOME;
            }

            /* select transform function and scan pattern according to plane and band number */
            switch ((p << 2) + i) {
            case 0:
                band->inv_transform  = ff_ivi_inverse_slant_8x8;
                band->dc_transform   = ff_ivi_dc_slant_2d;
                band->scan           = ff_zigzag_direct;
                band->transform_size = 8;
                break;

            case 1:
                band->inv_transform  = ff_ivi_row_slant8;
                band->dc_transform   = ff_ivi_dc_row_slant;
                band->scan           = ff_ivi_vertical_scan_8x8;
                band->transform_size = 8;
                break;

            case 2:
                band->inv_transform  = ff_ivi_col_slant8;
                band->dc_transform   = ff_ivi_dc_col_slant;
                band->scan           = ff_ivi_horizontal_scan_8x8;
                band->transform_size = 8;
                break;

            case 3:
                band->inv_transform  = ff_ivi_put_pixels_8x8;
                band->dc_transform   = ff_ivi_put_dc_pixel_8x8;
                band->scan           = ff_ivi_horizontal_scan_8x8;
                band->transform_size = 8;
                break;

            case 4:
                band->inv_transform  = ff_ivi_inverse_slant_4x4;
                band->dc_transform   = ff_ivi_dc_slant_2d;
                band->scan           = ff_ivi_direct_scan_4x4;
                band->transform_size = 4;
                break;
            }

            band->is_2d_trans = band->inv_transform == ff_ivi_inverse_slant_8x8 ||
                                band->inv_transform == ff_ivi_inverse_slant_4x4;

            if (band->transform_size != band->blk_size) {
                av_log(avctx, AV_LOG_ERROR, "transform and block size mismatch (%d != %d)\n", band->transform_size, band->blk_size);
                return AVERROR_INVALIDDATA;
            }

            /* select dequant matrix according to plane and band number */
            if (!p) {
                quant_mat = (pic_conf.luma_bands > 1) ? i+1 : 0;
            } else {
                quant_mat = 5;
            }

            if (band->blk_size == 8) {
                if(quant_mat >= 5){
                    av_log(avctx, AV_LOG_ERROR, "quant_mat %d too large!\n", quant_mat);
                    return -1;
                }
                band->intra_base  = &ivi5_base_quant_8x8_intra[quant_mat][0];
                band->inter_base  = &ivi5_base_quant_8x8_inter[quant_mat][0];
                band->intra_scale = &ivi5_scale_quant_8x8_intra[quant_mat][0];
                band->inter_scale = &ivi5_scale_quant_8x8_inter[quant_mat][0];
            } else {
                band->intra_base  = ivi5_base_quant_4x4_intra;
                band->inter_base  = ivi5_base_quant_4x4_inter;
                band->intra_scale = ivi5_scale_quant_4x4_intra;
                band->inter_scale = ivi5_scale_quant_4x4_inter;
            }

            if (get_bits(&ctx->gb, 2)) {
                av_log(avctx, AV_LOG_ERROR, "End marker missing!\n");
                return AVERROR_INVALIDDATA;
            }
        }
    }

    /* copy chroma parameters into the 2nd chroma plane */
    for (i = 0; i < pic_conf.chroma_bands; i++) {
        band1 = &ctx->planes[1].bands[i];
        band2 = &ctx->planes[2].bands[i];

        band2->width         = band1->width;
        band2->height        = band1->height;
        band2->mb_size       = band1->mb_size;
        band2->blk_size      = band1->blk_size;
        band2->is_halfpel    = band1->is_halfpel;
        band2->intra_base    = band1->intra_base;
        band2->inter_base    = band1->inter_base;
        band2->intra_scale   = band1->intra_scale;
        band2->inter_scale   = band1->inter_scale;
        band2->scan          = band1->scan;
        band2->inv_transform = band1->inv_transform;
        band2->dc_transform  = band1->dc_transform;
        band2->is_2d_trans   = band1->is_2d_trans;
        band2->transform_size= band1->transform_size;
    }

    /* reallocate internal structures if needed */
    if (blk_size_changed) {
        result = ff_ivi_init_tiles(ctx->planes, pic_conf.tile_width,
                                   pic_conf.tile_height);
        if (result < 0) {
            av_log(avctx, AV_LOG_ERROR,
                   "Couldn't reallocate internal structures!\n");
            return result;
        }
    }

    if (ctx->gop_flags & 8) {
        if (get_bits(&ctx->gb, 3)) {
            av_log(avctx, AV_LOG_ERROR, "Alignment bits are not zero!\n");
            return AVERROR_INVALIDDATA;
        }

        if (get_bits1(&ctx->gb))
            skip_bits_long(&ctx->gb, 24); /* skip transparency fill color */
    }

    align_get_bits(&ctx->gb);

    skip_bits(&ctx->gb, 23); /* FIXME: unknown meaning */

    /* skip GOP extension if any */
    if (get_bits1(&ctx->gb)) {
        do {
            i = get_bits(&ctx->gb, 16);
        } while (i & 0x8000);
    }

    align_get_bits(&ctx->gb);

    return 0;
}