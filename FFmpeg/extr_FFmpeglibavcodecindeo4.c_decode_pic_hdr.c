#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {TYPE_1__* bands; } ;
struct TYPE_20__ {int /*<<< orphan*/  max_pixels; } ;
struct TYPE_18__ {int pic_height; int pic_width; int tile_height; int tile_width; int chroma_height; int chroma_width; int luma_bands; int chroma_bands; } ;
struct TYPE_19__ {int prev_frame_type; int frame_type; int has_b_frames; int data_size; int is_scalable; int frame_num; int rvmap_sel; int pic_glob_quant; int unknown1; int checksum; int /*<<< orphan*/  gb; void* in_q; void* in_imf; int /*<<< orphan*/  blk_vlc; int /*<<< orphan*/  mb_vlc; TYPE_2__ pic_conf; TYPE_7__* planes; void* uses_tiling; void* has_transp; } ;
struct TYPE_17__ {int mb_size; int blk_size; } ;
typedef  TYPE_2__ IVIPicConfig ;
typedef  TYPE_3__ IVI45DecContext ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUV410P ; 
 int /*<<< orphan*/  ENOMEM ; 
 int IVI4_FRAMETYPE_BIDIR ; 
 int IVI4_FRAMETYPE_NULL_FIRST ; 
 int IVI4_PIC_SIZE_ESC ; 
 int /*<<< orphan*/  IVI_BLK_HUFF ; 
 int /*<<< orphan*/  IVI_MB_HUFF ; 
 int /*<<< orphan*/  align_get_bits (int /*<<< orphan*/ *) ; 
 scalar_t__ av_image_check_size2 (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 void* decode_plane_subdivision (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_dlog (TYPE_4__*,char*) ; 
 scalar_t__ ff_ivi_dec_huff_desc (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*) ; 
 scalar_t__ ff_ivi_init_planes (TYPE_4__*,TYPE_7__*,TYPE_2__*,int) ; 
 scalar_t__ ff_ivi_init_tiles (TYPE_7__*,int,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 void** ivi4_common_pic_sizes ; 
 scalar_t__ ivi_pic_config_cmp (TYPE_2__*,TYPE_2__*) ; 
 void* scale_tile_size (int,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int decode_pic_hdr(IVI45DecContext *ctx, AVCodecContext *avctx)
{
    int             pic_size_indx, i, p;
    IVIPicConfig    pic_conf;

    if (get_bits(&ctx->gb, 18) != 0x3FFF8) {
        av_log(avctx, AV_LOG_ERROR, "Invalid picture start code!\n");
        return AVERROR_INVALIDDATA;
    }

    ctx->prev_frame_type = ctx->frame_type;
    ctx->frame_type      = get_bits(&ctx->gb, 3);
    if (ctx->frame_type == 7) {
        av_log(avctx, AV_LOG_ERROR, "Invalid frame type: %d\n", ctx->frame_type);
        return AVERROR_INVALIDDATA;
    }

    if (ctx->frame_type == IVI4_FRAMETYPE_BIDIR)
        ctx->has_b_frames = 1;

    ctx->has_transp = get_bits1(&ctx->gb);

    /* unknown bit: Mac decoder ignores this bit, XANIM returns error */
    if (get_bits1(&ctx->gb)) {
        av_log(avctx, AV_LOG_ERROR, "Sync bit is set!\n");
        return AVERROR_INVALIDDATA;
    }

    ctx->data_size = get_bits1(&ctx->gb) ? get_bits(&ctx->gb, 24) : 0;

    /* null frames don't contain anything else so we just return */
    if (ctx->frame_type >= IVI4_FRAMETYPE_NULL_FIRST) {
        ff_dlog(avctx, "Null frame encountered!\n");
        return 0;
    }

    /* Check key lock status. If enabled - ignore lock word.         */
    /* Usually we have to prompt the user for the password, but      */
    /* we don't do that because Indeo 4 videos can be decoded anyway */
    if (get_bits1(&ctx->gb)) {
        skip_bits_long(&ctx->gb, 32);
        ff_dlog(avctx, "Password-protected clip!\n");
    }

    pic_size_indx = get_bits(&ctx->gb, 3);
    if (pic_size_indx == IVI4_PIC_SIZE_ESC) {
        pic_conf.pic_height = get_bits(&ctx->gb, 16);
        pic_conf.pic_width  = get_bits(&ctx->gb, 16);
    } else {
        pic_conf.pic_height = ivi4_common_pic_sizes[pic_size_indx * 2 + 1];
        pic_conf.pic_width  = ivi4_common_pic_sizes[pic_size_indx * 2    ];
    }

    /* Decode tile dimensions. */
    ctx->uses_tiling = get_bits1(&ctx->gb);
    if (ctx->uses_tiling) {
        pic_conf.tile_height = scale_tile_size(pic_conf.pic_height, get_bits(&ctx->gb, 4));
        pic_conf.tile_width  = scale_tile_size(pic_conf.pic_width,  get_bits(&ctx->gb, 4));
    } else {
        pic_conf.tile_height = pic_conf.pic_height;
        pic_conf.tile_width  = pic_conf.pic_width;
    }

    /* Decode chroma subsampling. We support only 4:4 aka YVU9. */
    if (get_bits(&ctx->gb, 2)) {
        av_log(avctx, AV_LOG_ERROR, "Only YVU9 picture format is supported!\n");
        return AVERROR_INVALIDDATA;
    }
    pic_conf.chroma_height = (pic_conf.pic_height + 3) >> 2;
    pic_conf.chroma_width  = (pic_conf.pic_width  + 3) >> 2;

    /* decode subdivision of the planes */
    pic_conf.luma_bands = decode_plane_subdivision(&ctx->gb);
    pic_conf.chroma_bands = 0;
    if (pic_conf.luma_bands)
        pic_conf.chroma_bands = decode_plane_subdivision(&ctx->gb);

    if (av_image_check_size2(pic_conf.pic_width, pic_conf.pic_height, avctx->max_pixels, AV_PIX_FMT_YUV410P, 0, avctx) < 0) {
        av_log(avctx, AV_LOG_ERROR, "picture dimensions %d %d cannot be decoded\n",
               pic_conf.pic_width, pic_conf.pic_height);
        return AVERROR_INVALIDDATA;
    }

    ctx->is_scalable = pic_conf.luma_bands != 1 || pic_conf.chroma_bands != 1;
    if (ctx->is_scalable && (pic_conf.luma_bands != 4 || pic_conf.chroma_bands != 1)) {
        av_log(avctx, AV_LOG_ERROR, "Scalability: unsupported subdivision! Luma bands: %d, chroma bands: %d\n",
               pic_conf.luma_bands, pic_conf.chroma_bands);
        return AVERROR_INVALIDDATA;
    }

    /* check if picture layout was changed and reallocate buffers */
    if (ivi_pic_config_cmp(&pic_conf, &ctx->pic_conf)) {
        if (ff_ivi_init_planes(avctx, ctx->planes, &pic_conf, 1)) {
            av_log(avctx, AV_LOG_ERROR, "Couldn't reallocate color planes!\n");
            ctx->pic_conf.luma_bands = 0;
            return AVERROR(ENOMEM);
        }

        ctx->pic_conf = pic_conf;

        /* set default macroblock/block dimensions */
        for (p = 0; p <= 2; p++) {
            for (i = 0; i < (!p ? pic_conf.luma_bands : pic_conf.chroma_bands); i++) {
                ctx->planes[p].bands[i].mb_size  = !p ? (!ctx->is_scalable ? 16 : 8) : 4;
                ctx->planes[p].bands[i].blk_size = !p ? 8 : 4;
            }
        }

        if (ff_ivi_init_tiles(ctx->planes, ctx->pic_conf.tile_width,
                              ctx->pic_conf.tile_height)) {
            av_log(avctx, AV_LOG_ERROR,
                   "Couldn't reallocate internal structures!\n");
            return AVERROR(ENOMEM);
        }
    }

    ctx->frame_num = get_bits1(&ctx->gb) ? get_bits(&ctx->gb, 20) : 0;

    /* skip decTimeEst field if present */
    if (get_bits1(&ctx->gb))
        skip_bits(&ctx->gb, 8);

    /* decode macroblock and block huffman codebooks */
    if (ff_ivi_dec_huff_desc(&ctx->gb, get_bits1(&ctx->gb), IVI_MB_HUFF,  &ctx->mb_vlc,  avctx) ||
        ff_ivi_dec_huff_desc(&ctx->gb, get_bits1(&ctx->gb), IVI_BLK_HUFF, &ctx->blk_vlc, avctx))
        return AVERROR_INVALIDDATA;

    ctx->rvmap_sel = get_bits1(&ctx->gb) ? get_bits(&ctx->gb, 3) : 8;

    ctx->in_imf = get_bits1(&ctx->gb);
    ctx->in_q   = get_bits1(&ctx->gb);

    ctx->pic_glob_quant = get_bits(&ctx->gb, 5);

    /* TODO: ignore this parameter if unused */
    ctx->unknown1 = get_bits1(&ctx->gb) ? get_bits(&ctx->gb, 3) : 0;

    ctx->checksum = get_bits1(&ctx->gb) ? get_bits(&ctx->gb, 16) : 0;

    /* skip picture header extension if any */
    while (get_bits1(&ctx->gb)) {
        ff_dlog(avctx, "Pic hdr extension encountered!\n");
        if (get_bits_left(&ctx->gb) < 10)
            return AVERROR_INVALIDDATA;
        skip_bits(&ctx->gb, 8);
    }

    if (get_bits1(&ctx->gb)) {
        av_log(avctx, AV_LOG_ERROR, "Bad blocks bits encountered!\n");
    }

    align_get_bits(&ctx->gb);

    return 0;
}