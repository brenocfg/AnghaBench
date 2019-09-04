#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {size_t dst_buf; scalar_t__ frame_type; size_t b_ref_buf; size_t ref_buf; int (* decode_band_hdr ) (TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ *) ;int (* decode_mb_info ) (TYPE_6__*,TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  gb; TYPE_2__* planes; TYPE_3__* rvmap_tabs; scalar_t__ frame_data; scalar_t__ is_indeo4; } ;
struct TYPE_22__ {size_t rvmap_sel; int num_corr; int* corr; int num_tiles; int mb_size; TYPE_3__* rv_map; TYPE_4__* tiles; scalar_t__ is_empty; scalar_t__ data_ptr; scalar_t__ b_ref_buf; scalar_t__* bufs; scalar_t__ ref_buf; scalar_t__ buf; } ;
struct TYPE_21__ {int mb_size; int data_size; scalar_t__ is_empty; } ;
struct TYPE_20__ {int eob_sym; int esc_sym; int /*<<< orphan*/ * valtab; int /*<<< orphan*/ * runtab; } ;
struct TYPE_19__ {TYPE_1__* bands; } ;
struct TYPE_18__ {int mb_size; } ;
typedef  TYPE_4__ IVITile ;
typedef  TYPE_5__ IVIBandDesc ;
typedef  TYPE_6__ IVI45DecContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  FFSWAP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IVI4_FRAMETYPE_BIDIR ; 
 int /*<<< orphan*/  align_get_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ff_dlog (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  int16_t ; 
 int ivi_dec_tile_data_size (int /*<<< orphan*/ *) ; 
 int ivi_decode_blocks (int /*<<< orphan*/ *,TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int ivi_process_empty_tile (int /*<<< orphan*/ *,TYPE_5__*,TYPE_4__*,int) ; 
 int stub1 (TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int stub2 (TYPE_6__*,TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uint8_t ; 

__attribute__((used)) static int decode_band(IVI45DecContext *ctx,
                       IVIBandDesc *band, AVCodecContext *avctx)
{
    int         result, i, t, idx1, idx2, pos;
    IVITile     *tile;

    band->buf     = band->bufs[ctx->dst_buf];
    if (!band->buf) {
        av_log(avctx, AV_LOG_ERROR, "Band buffer points to no data!\n");
        return AVERROR_INVALIDDATA;
    }
    if (ctx->is_indeo4 && ctx->frame_type == IVI4_FRAMETYPE_BIDIR) {
        band->ref_buf   = band->bufs[ctx->b_ref_buf];
        band->b_ref_buf = band->bufs[ctx->ref_buf];
    } else {
        band->ref_buf   = band->bufs[ctx->ref_buf];
        band->b_ref_buf = 0;
    }
    band->data_ptr  = ctx->frame_data + (get_bits_count(&ctx->gb) >> 3);

    result = ctx->decode_band_hdr(ctx, band, avctx);
    if (result) {
        av_log(avctx, AV_LOG_ERROR, "Error while decoding band header: %d\n",
               result);
        return result;
    }

    if (band->is_empty) {
        av_log(avctx, AV_LOG_ERROR, "Empty band encountered!\n");
        return AVERROR_INVALIDDATA;
    }

    band->rv_map = &ctx->rvmap_tabs[band->rvmap_sel];

    /* apply corrections to the selected rvmap table if present */
    for (i = 0; i < band->num_corr; i++) {
        idx1 = band->corr[i * 2];
        idx2 = band->corr[i * 2 + 1];
        FFSWAP(uint8_t, band->rv_map->runtab[idx1], band->rv_map->runtab[idx2]);
        FFSWAP(int16_t, band->rv_map->valtab[idx1], band->rv_map->valtab[idx2]);
        if (idx1 == band->rv_map->eob_sym || idx2 == band->rv_map->eob_sym)
            band->rv_map->eob_sym ^= idx1 ^ idx2;
        if (idx1 == band->rv_map->esc_sym || idx2 == band->rv_map->esc_sym)
            band->rv_map->esc_sym ^= idx1 ^ idx2;
    }

    pos = get_bits_count(&ctx->gb);

    for (t = 0; t < band->num_tiles; t++) {
        tile = &band->tiles[t];

        if (tile->mb_size != band->mb_size) {
            av_log(avctx, AV_LOG_ERROR, "MB sizes mismatch: %d vs. %d\n",
                   band->mb_size, tile->mb_size);
            return AVERROR_INVALIDDATA;
        }
        tile->is_empty = get_bits1(&ctx->gb);
        if (tile->is_empty) {
            result = ivi_process_empty_tile(avctx, band, tile,
                                      (ctx->planes[0].bands[0].mb_size >> 3) - (band->mb_size >> 3));
            if (result < 0)
                break;
            ff_dlog(avctx, "Empty tile encountered!\n");
        } else {
            tile->data_size = ivi_dec_tile_data_size(&ctx->gb);
            if (!tile->data_size) {
                av_log(avctx, AV_LOG_ERROR, "Tile data size is zero!\n");
                result = AVERROR_INVALIDDATA;
                break;
            }

            result = ctx->decode_mb_info(ctx, band, tile, avctx);
            if (result < 0)
                break;

            result = ivi_decode_blocks(&ctx->gb, band, tile, avctx);
            if (result < 0) {
                av_log(avctx, AV_LOG_ERROR,
                       "Corrupted tile data encountered!\n");
                break;
            }

            if (((get_bits_count(&ctx->gb) - pos) >> 3) != tile->data_size) {
                av_log(avctx, AV_LOG_ERROR,
                       "Tile data_size mismatch!\n");
                result = AVERROR_INVALIDDATA;
                break;
            }

            pos += tile->data_size << 3; // skip to next tile
        }
    }

    /* restore the selected rvmap table by applying its corrections in
     * reverse order */
    for (i = band->num_corr-1; i >= 0; i--) {
        idx1 = band->corr[i*2];
        idx2 = band->corr[i*2+1];
        FFSWAP(uint8_t, band->rv_map->runtab[idx1], band->rv_map->runtab[idx2]);
        FFSWAP(int16_t, band->rv_map->valtab[idx1], band->rv_map->valtab[idx2]);
        if (idx1 == band->rv_map->eob_sym || idx2 == band->rv_map->eob_sym)
            band->rv_map->eob_sym ^= idx1 ^ idx2;
        if (idx1 == band->rv_map->esc_sym || idx2 == band->rv_map->esc_sym)
            band->rv_map->esc_sym ^= idx1 ^ idx2;
    }

#ifdef DEBUG
    if (band->checksum_present) {
        uint16_t chksum = ivi_calc_band_checksum(band);
        if (chksum != band->checksum) {
            av_log(avctx, AV_LOG_ERROR,
                   "Band checksum mismatch! Plane %d, band %d, "
                   "received: %"PRIx32", calculated: %"PRIx16"\n",
                   band->plane, band->band_num, band->checksum, chksum);
        }
    }
#endif

    align_get_bits(&ctx->gb);

    return result;
}