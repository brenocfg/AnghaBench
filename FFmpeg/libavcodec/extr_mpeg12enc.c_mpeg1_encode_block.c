#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int int16_t ;
struct TYPE_10__ {int** table_vlc; } ;
struct TYPE_9__ {int** table_vlc; } ;
struct TYPE_7__ {int* permutated; } ;
struct TYPE_8__ {int* block_last_index; int* last_dc; scalar_t__ codec_id; int /*<<< orphan*/  pb; TYPE_1__ intra_scantable; scalar_t__ intra_vlc_format; scalar_t__ mb_intra; } ;
typedef  TYPE_2__ MpegEncContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_MPEG1VIDEO ; 
 int /*<<< orphan*/  MASK_ABS (int,int) ; 
 int abs (int) ; 
 int /*<<< orphan*/  encode_dc (TYPE_2__*,int,int) ; 
 TYPE_5__ ff_rl_mpeg1 ; 
 TYPE_4__ ff_rl_mpeg2 ; 
 int** mpeg1_index_run ; 
 int** mpeg1_max_level ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int const,int const) ; 
 int /*<<< orphan*/  put_sbits (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void mpeg1_encode_block(MpegEncContext *s, int16_t *block, int n)
{
    int alevel, level, last_non_zero, dc, diff, i, j, run, last_index, sign;
    int code, component;
    const uint16_t (*table_vlc)[2] = ff_rl_mpeg1.table_vlc;

    last_index = s->block_last_index[n];

    /* DC coef */
    if (s->mb_intra) {
        component = (n <= 3 ? 0 : (n & 1) + 1);
        dc        = block[0];                   /* overflow is impossible */
        diff      = dc - s->last_dc[component];
        encode_dc(s, diff, component);
        s->last_dc[component] = dc;
        i = 1;
        if (s->intra_vlc_format)
            table_vlc = ff_rl_mpeg2.table_vlc;
    } else {
        /* encode the first coefficient: needs to be done here because
         * it is handled slightly differently */
        level = block[0];
        if (abs(level) == 1) {
            code = ((uint32_t)level >> 31);     /* the sign bit */
            put_bits(&s->pb, 2, code | 0x02);
            i = 1;
        } else {
            i             = 0;
            last_non_zero = -1;
            goto next_coef;
        }
    }

    /* now quantify & encode AC coefs */
    last_non_zero = i - 1;

    for (; i <= last_index; i++) {
        j     = s->intra_scantable.permutated[i];
        level = block[j];

next_coef:
        /* encode using VLC */
        if (level != 0) {
            run = i - last_non_zero - 1;

            alevel = level;
            MASK_ABS(sign, alevel);
            sign &= 1;

            if (alevel <= mpeg1_max_level[0][run]) {
                code = mpeg1_index_run[0][run] + alevel - 1;
                /* store the VLC & sign at once */
                put_bits(&s->pb, table_vlc[code][1] + 1,
                         (table_vlc[code][0] << 1) + sign);
            } else {
                /* escape seems to be pretty rare <5% so I do not optimize it */
                put_bits(&s->pb, table_vlc[111][1], table_vlc[111][0]);
                /* escape: only clip in this case */
                put_bits(&s->pb, 6, run);
                if (s->codec_id == AV_CODEC_ID_MPEG1VIDEO) {
                    if (alevel < 128) {
                        put_sbits(&s->pb, 8, level);
                    } else {
                        if (level < 0)
                            put_bits(&s->pb, 16, 0x8001 + level + 255);
                        else
                            put_sbits(&s->pb, 16, level);
                    }
                } else {
                    put_sbits(&s->pb, 12, level);
                }
            }
            last_non_zero = i;
        }
    }
    /* end of block */
    put_bits(&s->pb, table_vlc[112][1], table_vlc[112][0]);
}