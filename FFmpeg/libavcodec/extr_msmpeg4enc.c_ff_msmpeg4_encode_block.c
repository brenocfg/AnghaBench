#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int int16_t ;
struct TYPE_10__ {size_t* permutated; } ;
struct TYPE_9__ {size_t* permutated; } ;
struct TYPE_12__ {int mb_intra; size_t rl_table_index; int rl_chroma_table_index; int msmpeg4_version; int* block_last_index; int esc3_level_length; int esc3_run_length; int qscale; int /*<<< orphan*/  pb; int /*<<< orphan*/ ***** ac_stats; TYPE_2__ inter_scantable; TYPE_1__ intra_scantable; } ;
struct TYPE_11__ {int** table_vlc; int n; int** max_level; int** max_run; } ;
typedef  TYPE_3__ RLTable ;
typedef  TYPE_4__ MpegEncContext ;

/* Variables and functions */
 int MAX_LEVEL ; 
 int MAX_RUN ; 
 TYPE_3__* ff_rl_table ; 
 int get_rl_index (TYPE_3__ const*,int,int,int) ; 
 int /*<<< orphan*/  msmpeg4_encode_dc (TYPE_4__*,int,int,int*) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  put_sbits (int /*<<< orphan*/ *,int,int) ; 

void ff_msmpeg4_encode_block(MpegEncContext * s, int16_t * block, int n)
{
    int level, run, last, i, j, last_index;
    int last_non_zero, sign, slevel;
    int code, run_diff, dc_pred_dir;
    const RLTable *rl;
    const uint8_t *scantable;

    if (s->mb_intra) {
        msmpeg4_encode_dc(s, block[0], n, &dc_pred_dir);
        i = 1;
        if (n < 4) {
            rl = &ff_rl_table[s->rl_table_index];
        } else {
            rl = &ff_rl_table[3 + s->rl_chroma_table_index];
        }
        run_diff = s->msmpeg4_version>=4;
        scantable= s->intra_scantable.permutated;
    } else {
        i = 0;
        rl = &ff_rl_table[3 + s->rl_table_index];
        if(s->msmpeg4_version<=2)
            run_diff = 0;
        else
            run_diff = 1;
        scantable= s->inter_scantable.permutated;
    }

    /* recalculate block_last_index for M$ wmv1 */
    if(s->msmpeg4_version>=4 && s->msmpeg4_version<6 && s->block_last_index[n]>0){
        for(last_index=63; last_index>=0; last_index--){
            if(block[scantable[last_index]]) break;
        }
        s->block_last_index[n]= last_index;
    }else
        last_index = s->block_last_index[n];
    /* AC coefs */
    last_non_zero = i - 1;
    for (; i <= last_index; i++) {
        j = scantable[i];
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

            if(level<=MAX_LEVEL && run<=MAX_RUN){
                s->ac_stats[s->mb_intra][n>3][level][run][last]++;
            }

            s->ac_stats[s->mb_intra][n > 3][40][63][0]++; //esc3 like

            code = get_rl_index(rl, last, run, level);
            put_bits(&s->pb, rl->table_vlc[code][1], rl->table_vlc[code][0]);
            if (code == rl->n) {
                int level1, run1;

                level1 = level - rl->max_level[last][run];
                if (level1 < 1)
                    goto esc2;
                code = get_rl_index(rl, last, run, level1);
                if (code == rl->n) {
                esc2:
                    put_bits(&s->pb, 1, 0);
                    if (level > MAX_LEVEL)
                        goto esc3;
                    run1 = run - rl->max_run[last][level] - run_diff;
                    if (run1 < 0)
                        goto esc3;
                    code = get_rl_index(rl, last, run1+1, level);
                    if (s->msmpeg4_version == 4 && code == rl->n)
                        goto esc3;
                    code = get_rl_index(rl, last, run1, level);
                    if (code == rl->n) {
                    esc3:
                        /* third escape */
                        put_bits(&s->pb, 1, 0);
                        put_bits(&s->pb, 1, last);
                        if(s->msmpeg4_version>=4){
                            if(s->esc3_level_length==0){
                                s->esc3_level_length=8;
                                s->esc3_run_length= 6;
                                //ESCLVLSZ + ESCRUNSZ
                                if(s->qscale<8)
                                    put_bits(&s->pb, 6 + (s->msmpeg4_version>=6), 3);
                                else
                                    put_bits(&s->pb, 8, 3);
                            }
                            put_bits(&s->pb, s->esc3_run_length, run);
                            put_bits(&s->pb, 1, sign);
                            put_bits(&s->pb, s->esc3_level_length, level);
                        }else{
                            put_bits(&s->pb, 6, run);
                            put_sbits(&s->pb, 8, slevel);
                        }
                    } else {
                        /* second escape */
                        put_bits(&s->pb, 1, 1);
                        put_bits(&s->pb, rl->table_vlc[code][1], rl->table_vlc[code][0]);
                        put_bits(&s->pb, 1, sign);
                    }
                } else {
                    /* first escape */
                    put_bits(&s->pb, 1, 1);
                    put_bits(&s->pb, rl->table_vlc[code][1], rl->table_vlc[code][0]);
                    put_bits(&s->pb, 1, sign);
                }
            } else {
                put_bits(&s->pb, 1, sign);
            }
            last_non_zero = i;
        }
    }
}