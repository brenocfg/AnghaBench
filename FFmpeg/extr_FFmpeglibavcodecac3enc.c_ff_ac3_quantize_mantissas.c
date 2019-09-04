#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * end_freq; int /*<<< orphan*/ * qmant; int /*<<< orphan*/ * exp; int /*<<< orphan*/ * fixed_coef; scalar_t__* channel_in_cpl; int /*<<< orphan*/  cpl_in_use; } ;
struct TYPE_7__ {int num_blocks; int channels; size_t** exp_ref_block; int /*<<< orphan*/ * start_freq; int /*<<< orphan*/ ** ref_bap; TYPE_3__* blocks; } ;
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ AC3Mant ;
typedef  TYPE_2__ AC3EncodeContext ;
typedef  TYPE_3__ AC3Block ;

/* Variables and functions */
 int CPL_CH ; 
 int /*<<< orphan*/  quantize_mantissas_blk_ch (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ff_ac3_quantize_mantissas(AC3EncodeContext *s)
{
    int blk, ch, ch0=0, got_cpl;

    for (blk = 0; blk < s->num_blocks; blk++) {
        AC3Block *block = &s->blocks[blk];
        AC3Mant m = { 0 };

        got_cpl = !block->cpl_in_use;
        for (ch = 1; ch <= s->channels; ch++) {
            if (!got_cpl && ch > 1 && block->channel_in_cpl[ch-1]) {
                ch0     = ch - 1;
                ch      = CPL_CH;
                got_cpl = 1;
            }
            quantize_mantissas_blk_ch(&m, block->fixed_coef[ch],
                                      s->blocks[s->exp_ref_block[ch][blk]].exp[ch],
                                      s->ref_bap[ch][blk], block->qmant[ch],
                                      s->start_freq[ch], block->end_freq[ch]);
            if (ch == CPL_CH)
                ch = ch0;
        }
    }
}