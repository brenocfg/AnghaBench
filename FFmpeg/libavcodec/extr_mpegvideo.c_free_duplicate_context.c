#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  score_map; int /*<<< orphan*/  map; int /*<<< orphan*/  temp; int /*<<< orphan*/  scratchpad; } ;
struct TYPE_5__ {int /*<<< orphan*/ * obmc_scratchpad; int /*<<< orphan*/  b_scratchpad; int /*<<< orphan*/  rd_scratchpad; int /*<<< orphan*/  edge_emu_buffer; } ;
struct TYPE_7__ {int /*<<< orphan*/ * block; int /*<<< orphan*/  ac_val_base; int /*<<< orphan*/  dpcm_macroblock; int /*<<< orphan*/  block32; int /*<<< orphan*/  blocks; TYPE_2__ me; int /*<<< orphan*/  dct_error_sum; TYPE_1__ sc; } ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_duplicate_context(MpegEncContext *s)
{
    if (!s)
        return;

    av_freep(&s->sc.edge_emu_buffer);
    av_freep(&s->me.scratchpad);
    s->me.temp =
    s->sc.rd_scratchpad =
    s->sc.b_scratchpad =
    s->sc.obmc_scratchpad = NULL;

    av_freep(&s->dct_error_sum);
    av_freep(&s->me.map);
    av_freep(&s->me.score_map);
    av_freep(&s->blocks);
    av_freep(&s->block32);
    av_freep(&s->dpcm_macroblock);
    av_freep(&s->ac_val_base);
    s->block = NULL;
}