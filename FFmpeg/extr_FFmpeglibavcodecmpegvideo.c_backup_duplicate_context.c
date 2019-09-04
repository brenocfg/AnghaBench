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
struct TYPE_7__ {int /*<<< orphan*/  map_generation; int /*<<< orphan*/  score_map; int /*<<< orphan*/  map; int /*<<< orphan*/  temp; int /*<<< orphan*/  scratchpad; } ;
struct TYPE_6__ {int /*<<< orphan*/  obmc_scratchpad; int /*<<< orphan*/  b_scratchpad; int /*<<< orphan*/  rd_scratchpad; int /*<<< orphan*/  edge_emu_buffer; } ;
struct TYPE_8__ {int /*<<< orphan*/ * ac_val; int /*<<< orphan*/  ac_val_base; int /*<<< orphan*/ * dct_count; int /*<<< orphan*/  dct_error_sum; int /*<<< orphan*/  pb; TYPE_2__ me; int /*<<< orphan*/  end_mb_y; int /*<<< orphan*/  start_mb_y; int /*<<< orphan*/  dpcm_direction; int /*<<< orphan*/  dpcm_macroblock; int /*<<< orphan*/  block32; int /*<<< orphan*/  block; int /*<<< orphan*/  blocks; TYPE_1__ sc; } ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */

__attribute__((used)) static void backup_duplicate_context(MpegEncContext *bak, MpegEncContext *src)
{
#define COPY(a) bak->a = src->a
    COPY(sc.edge_emu_buffer);
    COPY(me.scratchpad);
    COPY(me.temp);
    COPY(sc.rd_scratchpad);
    COPY(sc.b_scratchpad);
    COPY(sc.obmc_scratchpad);
    COPY(me.map);
    COPY(me.score_map);
    COPY(blocks);
    COPY(block);
    COPY(block32);
    COPY(dpcm_macroblock);
    COPY(dpcm_direction);
    COPY(start_mb_y);
    COPY(end_mb_y);
    COPY(me.map_generation);
    COPY(pb);
    COPY(dct_error_sum);
    COPY(dct_count[0]);
    COPY(dct_count[1]);
    COPY(ac_val_base);
    COPY(ac_val[0]);
    COPY(ac_val[1]);
    COPY(ac_val[2]);
#undef COPY
}