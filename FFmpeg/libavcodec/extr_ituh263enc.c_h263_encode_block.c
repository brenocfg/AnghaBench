#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int int16_t ;
struct TYPE_8__ {int* permutated; } ;
struct TYPE_10__ {int* block_last_index; int h263_flv; int /*<<< orphan*/  pb; TYPE_1__ intra_scantable; scalar_t__ mb_intra; scalar_t__ alt_inter_vlc; scalar_t__ h263_aic; } ;
struct TYPE_9__ {int** table_vlc; int n; } ;
typedef  TYPE_2__ RLTable ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_FLV_ENCODER ; 
 int /*<<< orphan*/  av_assert2 (int) ; 
 int /*<<< orphan*/  ff_flv2_encode_ac_esc (int /*<<< orphan*/ *,int,int,int,int) ; 
 TYPE_2__ ff_h263_rl_inter ; 
 TYPE_2__ ff_rl_intra_aic ; 
 int get_rl_index (TYPE_2__*,int,int,int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  put_sbits (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__* wrong_run ; 

__attribute__((used)) static void h263_encode_block(MpegEncContext * s, int16_t * block, int n)
{
    int level, run, last, i, j, last_index, last_non_zero, sign, slevel, code;
    RLTable *rl;

    rl = &ff_h263_rl_inter;
    if (s->mb_intra && !s->h263_aic) {
        /* DC coef */
        level = block[0];
        /* 255 cannot be represented, so we clamp */
        if (level > 254) {
            level = 254;
            block[0] = 254;
        }
        /* 0 cannot be represented also */
        else if (level < 1) {
            level = 1;
            block[0] = 1;
        }
        if (level == 128) //FIXME check rv10
            put_bits(&s->pb, 8, 0xff);
        else
            put_bits(&s->pb, 8, level);
        i = 1;
    } else {
        i = 0;
        if (s->h263_aic && s->mb_intra)
            rl = &ff_rl_intra_aic;

        if(s->alt_inter_vlc && !s->mb_intra){
            int aic_vlc_bits=0;
            int inter_vlc_bits=0;
            int wrong_pos=-1;
            int aic_code;

            last_index = s->block_last_index[n];
            last_non_zero = i - 1;
            for (; i <= last_index; i++) {
                j = s->intra_scantable.permutated[i];
                level = block[j];
                if (level) {
                    run = i - last_non_zero - 1;
                    last = (i == last_index);

                    if(level<0) level= -level;

                    code = get_rl_index(rl, last, run, level);
                    aic_code = get_rl_index(&ff_rl_intra_aic, last, run, level);
                    inter_vlc_bits += rl->table_vlc[code][1]+1;
                    aic_vlc_bits   += ff_rl_intra_aic.table_vlc[aic_code][1]+1;

                    if (code == rl->n) {
                        inter_vlc_bits += 1+6+8-1;
                    }
                    if (aic_code == ff_rl_intra_aic.n) {
                        aic_vlc_bits += 1+6+8-1;
                        wrong_pos += run + 1;
                    }else
                        wrong_pos += wrong_run[aic_code];
                    last_non_zero = i;
                }
            }
            i = 0;
            if(aic_vlc_bits < inter_vlc_bits && wrong_pos > 63)
                rl = &ff_rl_intra_aic;
        }
    }

    /* AC coefs */
    last_index = s->block_last_index[n];
    last_non_zero = i - 1;
    for (; i <= last_index; i++) {
        j = s->intra_scantable.permutated[i];
        level = block[j];
        if (level) {
            run = i - last_non_zero - 1;
            last = (i == last_index);
            sign = 0;
            slevel = level;
            if (level < 0) {
                sign = 1;
                level = -level;
            }
            code = get_rl_index(rl, last, run, level);
            put_bits(&s->pb, rl->table_vlc[code][1], rl->table_vlc[code][0]);
            if (code == rl->n) {
              if(!CONFIG_FLV_ENCODER || s->h263_flv <= 1){
                put_bits(&s->pb, 1, last);
                put_bits(&s->pb, 6, run);

                av_assert2(slevel != 0);

                if(level < 128)
                    put_sbits(&s->pb, 8, slevel);
                else{
                    put_bits(&s->pb, 8, 128);
                    put_sbits(&s->pb, 5, slevel);
                    put_sbits(&s->pb, 6, slevel>>5);
                }
              }else{
                    ff_flv2_encode_ac_esc(&s->pb, slevel, level, run, last);
              }
            } else {
                put_bits(&s->pb, 1, sign);
            }
            last_non_zero = i;
        }
    }
}