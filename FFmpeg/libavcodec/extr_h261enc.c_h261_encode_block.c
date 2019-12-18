#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int int16_t ;
struct TYPE_8__ {int* permutated; } ;
struct TYPE_10__ {int* block_last_index; int /*<<< orphan*/  pb; TYPE_1__ intra_scantable; scalar_t__ mb_intra; } ;
struct TYPE_11__ {TYPE_3__ s; } ;
struct TYPE_9__ {int** table_vlc; int n; } ;
typedef  TYPE_2__ RLTable ;
typedef  TYPE_3__ MpegEncContext ;
typedef  TYPE_4__ H261Context ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert1 (int) ; 
 TYPE_2__ ff_h261_rl_tcoeff ; 
 int get_rl_index (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  put_sbits (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void h261_encode_block(H261Context *h, int16_t *block, int n)
{
    MpegEncContext *const s = &h->s;
    int level, run, i, j, last_index, last_non_zero, sign, slevel, code;
    RLTable *rl;

    rl = &ff_h261_rl_tcoeff;
    if (s->mb_intra) {
        /* DC coef */
        level = block[0];
        /* 255 cannot be represented, so we clamp */
        if (level > 254) {
            level    = 254;
            block[0] = 254;
        }
        /* 0 cannot be represented also */
        else if (level < 1) {
            level    = 1;
            block[0] = 1;
        }
        if (level == 128)
            put_bits(&s->pb, 8, 0xff);
        else
            put_bits(&s->pb, 8, level);
        i = 1;
    } else if ((block[0] == 1 || block[0] == -1) &&
               (s->block_last_index[n] > -1)) {
        // special case
        put_bits(&s->pb, 2, block[0] > 0 ? 2 : 3);
        i = 1;
    } else {
        i = 0;
    }

    /* AC coefs */
    last_index    = s->block_last_index[n];
    last_non_zero = i - 1;
    for (; i <= last_index; i++) {
        j     = s->intra_scantable.permutated[i];
        level = block[j];
        if (level) {
            run    = i - last_non_zero - 1;
            sign   = 0;
            slevel = level;
            if (level < 0) {
                sign  = 1;
                level = -level;
            }
            code = get_rl_index(rl, 0 /*no last in H.261, EOB is used*/,
                                run, level);
            if (run == 0 && level < 16)
                code += 1;
            put_bits(&s->pb, rl->table_vlc[code][1], rl->table_vlc[code][0]);
            if (code == rl->n) {
                put_bits(&s->pb, 6, run);
                av_assert1(slevel != 0);
                av_assert1(level <= 127);
                put_sbits(&s->pb, 8, slevel);
            } else {
                put_bits(&s->pb, 1, sign);
            }
            last_non_zero = i;
        }
    }
    if (last_index > -1)
        put_bits(&s->pb, rl->table_vlc[0][1], rl->table_vlc[0][0]); // EOB
}