#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int blocksize; int* bs_code; scalar_t__ verbatim_only; TYPE_3__* subframes; } ;
struct TYPE_11__ {int channels; TYPE_1__* avctx; TYPE_4__ frame; } ;
struct TYPE_8__ {int /*<<< orphan*/  coding_mode; } ;
struct TYPE_9__ {int obits; TYPE_2__ rc; scalar_t__ wasted; } ;
struct TYPE_7__ {int bits_per_raw_sample; } ;
typedef  TYPE_3__ FlacSubframe ;
typedef  TYPE_4__ FlacFrame ;
typedef  TYPE_5__ FlacEncodeContext ;

/* Variables and functions */
 int /*<<< orphan*/  CODING_MODE_RICE ; 
 int /*<<< orphan*/  CODING_MODE_RICE2 ; 
 int* ff_flac_blocksize_table ; 

__attribute__((used)) static void init_frame(FlacEncodeContext *s, int nb_samples)
{
    int i, ch;
    FlacFrame *frame;

    frame = &s->frame;

    for (i = 0; i < 16; i++) {
        if (nb_samples == ff_flac_blocksize_table[i]) {
            frame->blocksize  = ff_flac_blocksize_table[i];
            frame->bs_code[0] = i;
            frame->bs_code[1] = 0;
            break;
        }
    }
    if (i == 16) {
        frame->blocksize = nb_samples;
        if (frame->blocksize <= 256) {
            frame->bs_code[0] = 6;
            frame->bs_code[1] = frame->blocksize-1;
        } else {
            frame->bs_code[0] = 7;
            frame->bs_code[1] = frame->blocksize-1;
        }
    }

    for (ch = 0; ch < s->channels; ch++) {
        FlacSubframe *sub = &frame->subframes[ch];

        sub->wasted = 0;
        sub->obits  = s->avctx->bits_per_raw_sample;

        if (sub->obits > 16)
            sub->rc.coding_mode = CODING_MODE_RICE2;
        else
            sub->rc.coding_mode = CODING_MODE_RICE;
    }

    frame->verbatim_only = 0;
}