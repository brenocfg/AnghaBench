#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* tab; } ;
struct TYPE_19__ {scalar_t__ frame_type; int /*<<< orphan*/  gb; TYPE_2__ mb_vlc; scalar_t__ in_q; TYPE_4__* planes; } ;
struct TYPE_18__ {int mb_size; int pitch; int blk_size; int is_halfpel; int bufsize; scalar_t__ inherit_mv; int /*<<< orphan*/  band_num; int /*<<< orphan*/  plane; scalar_t__ inherit_qdelta; } ;
struct TYPE_17__ {int xpos; int ypos; int buf_offs; int b_mv_x; int b_mv_y; int type; int q_delta; int mv_x; int mv_y; void* cbp; } ;
struct TYPE_16__ {int ypos; int xpos; int width; int height; int num_MBs; TYPE_6__* ref_mbs; TYPE_6__* mbs; } ;
struct TYPE_15__ {TYPE_3__* bands; } ;
struct TYPE_14__ {int mb_size; } ;
struct TYPE_12__ {int /*<<< orphan*/  table; } ;
typedef  TYPE_5__ IVITile ;
typedef  TYPE_6__ IVIMbInfo ;
typedef  TYPE_7__ IVIBandDesc ;
typedef  TYPE_8__ IVI45DecContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ IVI4_FRAMETYPE_BIDIR ; 
 scalar_t__ IVI4_FRAMETYPE_INTRA ; 
 scalar_t__ IVI4_FRAMETYPE_INTRA1 ; 
 void* IVI_TOSIGNED (int) ; 
 int /*<<< orphan*/  IVI_VLC_BITS ; 
 int /*<<< orphan*/  align_get_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 void* get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* ivi_scale_mv (int,int) ; 

__attribute__((used)) static int decode_mb_info(IVI45DecContext *ctx, IVIBandDesc *band,
                          IVITile *tile, AVCodecContext *avctx)
{
    int         x, y, mv_x, mv_y, mv_delta, offs, mb_offset, blks_per_mb,
                mv_scale, mb_type_bits, s;
    IVIMbInfo   *mb, *ref_mb;
    int         row_offset = band->mb_size * band->pitch;

    mb     = tile->mbs;
    ref_mb = tile->ref_mbs;
    offs   = tile->ypos * band->pitch + tile->xpos;

    blks_per_mb  = band->mb_size   != band->blk_size  ? 4 : 1;
    mb_type_bits = ctx->frame_type == IVI4_FRAMETYPE_BIDIR ? 2 : 1;

    /* scale factor for motion vectors */
    mv_scale = (ctx->planes[0].bands[0].mb_size >> 3) - (band->mb_size >> 3);
    mv_x = mv_y = 0;

    if (((tile->width + band->mb_size-1)/band->mb_size) * ((tile->height + band->mb_size-1)/band->mb_size) != tile->num_MBs) {
        av_log(avctx, AV_LOG_ERROR, "num_MBs mismatch %d %d %d %d\n", tile->width, tile->height, band->mb_size, tile->num_MBs);
        return -1;
    }

    for (y = tile->ypos; y < tile->ypos + tile->height; y += band->mb_size) {
        mb_offset = offs;

        for (x = tile->xpos; x < tile->xpos + tile->width; x += band->mb_size) {
            mb->xpos     = x;
            mb->ypos     = y;
            mb->buf_offs = mb_offset;
            mb->b_mv_x   =
            mb->b_mv_y   = 0;

            if (get_bits_left(&ctx->gb) < 1) {
                av_log(avctx, AV_LOG_ERROR, "Insufficient input for mb info\n");
                return AVERROR_INVALIDDATA;
            }

            if (get_bits1(&ctx->gb)) {
                if (ctx->frame_type == IVI4_FRAMETYPE_INTRA) {
                    av_log(avctx, AV_LOG_ERROR, "Empty macroblock in an INTRA picture!\n");
                    return AVERROR_INVALIDDATA;
                }
                mb->type = 1; /* empty macroblocks are always INTER */
                mb->cbp  = 0; /* all blocks are empty */

                mb->q_delta = 0;
                if (!band->plane && !band->band_num && ctx->in_q) {
                    mb->q_delta = get_vlc2(&ctx->gb, ctx->mb_vlc.tab->table,
                                           IVI_VLC_BITS, 1);
                    mb->q_delta = IVI_TOSIGNED(mb->q_delta);
                }

                mb->mv_x = mb->mv_y = 0; /* no motion vector coded */
                if (band->inherit_mv && ref_mb) {
                    /* motion vector inheritance */
                    if (mv_scale) {
                        mb->mv_x = ivi_scale_mv(ref_mb->mv_x, mv_scale);
                        mb->mv_y = ivi_scale_mv(ref_mb->mv_y, mv_scale);
                    } else {
                        mb->mv_x = ref_mb->mv_x;
                        mb->mv_y = ref_mb->mv_y;
                    }
                }
            } else {
                if (band->inherit_mv) {
                    /* copy mb_type from corresponding reference mb */
                    if (!ref_mb) {
                        av_log(avctx, AV_LOG_ERROR, "ref_mb unavailable\n");
                        return AVERROR_INVALIDDATA;
                    }
                    mb->type = ref_mb->type;
                } else if (ctx->frame_type == IVI4_FRAMETYPE_INTRA ||
                           ctx->frame_type == IVI4_FRAMETYPE_INTRA1) {
                    mb->type = 0; /* mb_type is always INTRA for intra-frames */
                } else {
                    mb->type = get_bits(&ctx->gb, mb_type_bits);
                }

                mb->cbp = get_bits(&ctx->gb, blks_per_mb);

                mb->q_delta = 0;
                if (band->inherit_qdelta) {
                    if (ref_mb) mb->q_delta = ref_mb->q_delta;
                } else if (mb->cbp || (!band->plane && !band->band_num &&
                           ctx->in_q)) {
                    mb->q_delta = get_vlc2(&ctx->gb, ctx->mb_vlc.tab->table,
                                           IVI_VLC_BITS, 1);
                    mb->q_delta = IVI_TOSIGNED(mb->q_delta);
                }

                if (!mb->type) {
                    mb->mv_x = mb->mv_y = 0; /* there is no motion vector in intra-macroblocks */
                } else {
                    if (band->inherit_mv) {
                        if (ref_mb)
                            /* motion vector inheritance */
                            if (mv_scale) {
                                mb->mv_x = ivi_scale_mv(ref_mb->mv_x, mv_scale);
                                mb->mv_y = ivi_scale_mv(ref_mb->mv_y, mv_scale);
                            } else {
                                mb->mv_x = ref_mb->mv_x;
                                mb->mv_y = ref_mb->mv_y;
                            }
                    } else {
                        /* decode motion vector deltas */
                        mv_delta = get_vlc2(&ctx->gb, ctx->mb_vlc.tab->table,
                                            IVI_VLC_BITS, 1);
                        mv_y += IVI_TOSIGNED(mv_delta);
                        mv_delta = get_vlc2(&ctx->gb, ctx->mb_vlc.tab->table,
                                            IVI_VLC_BITS, 1);
                        mv_x += IVI_TOSIGNED(mv_delta);
                        mb->mv_x = mv_x;
                        mb->mv_y = mv_y;
                        if (mb->type == 3) {
                            mv_delta = get_vlc2(&ctx->gb,
                                                ctx->mb_vlc.tab->table,
                                                IVI_VLC_BITS, 1);
                            mv_y += IVI_TOSIGNED(mv_delta);
                            mv_delta = get_vlc2(&ctx->gb,
                                                ctx->mb_vlc.tab->table,
                                                IVI_VLC_BITS, 1);
                            mv_x += IVI_TOSIGNED(mv_delta);
                            mb->b_mv_x = -mv_x;
                            mb->b_mv_y = -mv_y;
                        }
                    }
                    if (mb->type == 2) {
                        mb->b_mv_x = -mb->mv_x;
                        mb->b_mv_y = -mb->mv_y;
                        mb->mv_x = 0;
                        mb->mv_y = 0;
                    }
                }
            }

            s= band->is_halfpel;
            if (mb->type)
            if ( x +  (mb->mv_x   >>s) +                 (y+               (mb->mv_y   >>s))*band->pitch < 0 ||
                 x + ((mb->mv_x+s)>>s) + band->mb_size - 1
                   + (y+band->mb_size - 1 +((mb->mv_y+s)>>s))*band->pitch > band->bufsize -1) {
                av_log(avctx, AV_LOG_ERROR, "motion vector %d %d outside reference\n", x*s + mb->mv_x, y*s + mb->mv_y);
                return AVERROR_INVALIDDATA;
            }

            mb++;
            if (ref_mb)
                ref_mb++;
            mb_offset += band->mb_size;
        }

        offs += row_offset;
    }

    align_get_bits(&ctx->gb);

    return 0;
}