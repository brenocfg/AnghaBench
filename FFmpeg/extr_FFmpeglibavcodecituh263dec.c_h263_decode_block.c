#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int int8_t ;
typedef  int int16_t ;
struct TYPE_14__ {int /*<<< orphan*/  (* clear_block ) (int*) ;} ;
struct TYPE_17__ {size_t* permutated; } ;
struct TYPE_16__ {size_t* permutated; } ;
struct TYPE_15__ {size_t* permutated; } ;
struct TYPE_19__ {int mb_intra; scalar_t__ codec_id; int rv10_version; scalar_t__ pict_type; int* last_dc; int* rv10_first_dc_coded; int mb_x; int mb_y; int* block_last_index; int h263_flv; scalar_t__ h263_aic; TYPE_12__* avctx; TYPE_1__ bdsp; int /*<<< orphan*/  gb; scalar_t__ alt_inter_vlc; TYPE_4__ intra_h_scantable; TYPE_3__ intra_v_scantable; scalar_t__ h263_aic_dir; scalar_t__ ac_pred; TYPE_2__ intra_scantable; } ;
struct TYPE_18__ {int /*<<< orphan*/ * rl_vlc; } ;
struct TYPE_13__ {int err_recognition; } ;
typedef  TYPE_5__ RLTable ;
typedef  TYPE_6__ MpegEncContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_RV10 ; 
 int AV_EF_BITSTREAM ; 
 int AV_EF_COMPLIANT ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/  CLOSE_READER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CONFIG_FLV_DECODER ; 
 scalar_t__ CONFIG_RV10_DECODER ; 
 int /*<<< orphan*/  GET_RL_VLC (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPEN_READER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int SHOW_SBITS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int SHOW_UBITS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SKIP_CACHE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SKIP_COUNTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TEX_VLC_BITS ; 
 int /*<<< orphan*/  UPDATE_CACHE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_12__*,int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  ff_h263_pred_acdc (TYPE_6__*,int*,int) ; 
 TYPE_5__ ff_h263_rl_inter ; 
 TYPE_5__ ff_rl_intra_aic ; 
 int ff_rv_decode_dc (TYPE_6__*,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  re ; 
 int /*<<< orphan*/  stub1 (int*) ; 

__attribute__((used)) static int h263_decode_block(MpegEncContext * s, int16_t * block,
                             int n, int coded)
{
    int level, i, j, run;
    RLTable *rl = &ff_h263_rl_inter;
    const uint8_t *scan_table;
    GetBitContext gb= s->gb;

    scan_table = s->intra_scantable.permutated;
    if (s->h263_aic && s->mb_intra) {
        rl = &ff_rl_intra_aic;
        i = 0;
        if (s->ac_pred) {
            if (s->h263_aic_dir)
                scan_table = s->intra_v_scantable.permutated; /* left */
            else
                scan_table = s->intra_h_scantable.permutated; /* top */
        }
    } else if (s->mb_intra) {
        /* DC coef */
        if (CONFIG_RV10_DECODER && s->codec_id == AV_CODEC_ID_RV10) {
          if (s->rv10_version == 3 && s->pict_type == AV_PICTURE_TYPE_I) {
            int component, diff;
            component = (n <= 3 ? 0 : n - 4 + 1);
            level = s->last_dc[component];
            if (s->rv10_first_dc_coded[component]) {
                diff = ff_rv_decode_dc(s, n);
                if (diff == 0xffff)
                    return -1;
                level += diff;
                level = level & 0xff; /* handle wrap round */
                s->last_dc[component] = level;
            } else {
                s->rv10_first_dc_coded[component] = 1;
            }
          } else {
                level = get_bits(&s->gb, 8);
                if (level == 255)
                    level = 128;
          }
        }else{
            level = get_bits(&s->gb, 8);
            if((level&0x7F) == 0){
                av_log(s->avctx, AV_LOG_ERROR, "illegal dc %d at %d %d\n", level, s->mb_x, s->mb_y);
                if (s->avctx->err_recognition & (AV_EF_BITSTREAM|AV_EF_COMPLIANT))
                    return -1;
            }
            if (level == 255)
                level = 128;
        }
        block[0] = level;
        i = 1;
    } else {
        i = 0;
    }
    if (!coded) {
        if (s->mb_intra && s->h263_aic)
            goto not_coded;
        s->block_last_index[n] = i - 1;
        return 0;
    }
retry:
    {
    OPEN_READER(re, &s->gb);
    i--; // offset by -1 to allow direct indexing of scan_table
    for(;;) {
        UPDATE_CACHE(re, &s->gb);
        GET_RL_VLC(level, run, re, &s->gb, rl->rl_vlc[0], TEX_VLC_BITS, 2, 0);
        if (run == 66) {
            if (level){
                CLOSE_READER(re, &s->gb);
                av_log(s->avctx, AV_LOG_ERROR, "illegal ac vlc code at %dx%d\n", s->mb_x, s->mb_y);
                return -1;
            }
            /* escape */
            if (CONFIG_FLV_DECODER && s->h263_flv > 1) {
                int is11 = SHOW_UBITS(re, &s->gb, 1);
                SKIP_CACHE(re, &s->gb, 1);
                run = SHOW_UBITS(re, &s->gb, 7) + 1;
                if (is11) {
                    SKIP_COUNTER(re, &s->gb, 1 + 7);
                    UPDATE_CACHE(re, &s->gb);
                    level = SHOW_SBITS(re, &s->gb, 11);
                    SKIP_COUNTER(re, &s->gb, 11);
                } else {
                    SKIP_CACHE(re, &s->gb, 7);
                    level = SHOW_SBITS(re, &s->gb, 7);
                    SKIP_COUNTER(re, &s->gb, 1 + 7 + 7);
                }
            } else {
                run = SHOW_UBITS(re, &s->gb, 7) + 1;
                SKIP_CACHE(re, &s->gb, 7);
                level = (int8_t)SHOW_UBITS(re, &s->gb, 8);
                SKIP_COUNTER(re, &s->gb, 7 + 8);
                if(level == -128){
                    UPDATE_CACHE(re, &s->gb);
                    if (s->codec_id == AV_CODEC_ID_RV10) {
                        /* XXX: should patch encoder too */
                        level = SHOW_SBITS(re, &s->gb, 12);
                        SKIP_COUNTER(re, &s->gb, 12);
                    }else{
                        level = SHOW_UBITS(re, &s->gb, 5);
                        SKIP_CACHE(re, &s->gb, 5);
                        level |= SHOW_SBITS(re, &s->gb, 6) * (1<<5);
                        SKIP_COUNTER(re, &s->gb, 5 + 6);
                    }
                }
            }
        } else {
            if (SHOW_UBITS(re, &s->gb, 1))
                level = -level;
            SKIP_COUNTER(re, &s->gb, 1);
        }
        i += run;
        if (i >= 64){
            CLOSE_READER(re, &s->gb);
            // redo update without last flag, revert -1 offset
            i = i - run + ((run-1)&63) + 1;
            if (i < 64) {
                // only last marker, no overrun
                block[scan_table[i]] = level;
                break;
            }
            if(s->alt_inter_vlc && rl == &ff_h263_rl_inter && !s->mb_intra){
                //Looks like a hack but no, it's the way it is supposed to work ...
                rl = &ff_rl_intra_aic;
                i = 0;
                s->gb= gb;
                s->bdsp.clear_block(block);
                goto retry;
            }
            av_log(s->avctx, AV_LOG_ERROR, "run overflow at %dx%d i:%d\n", s->mb_x, s->mb_y, s->mb_intra);
            return -1;
        }
        j = scan_table[i];
        block[j] = level;
    }
    }
not_coded:
    if (s->mb_intra && s->h263_aic) {
        ff_h263_pred_acdc(s, block, n);
        i = 63;
    }
    s->block_last_index[n] = i;
    return 0;
}