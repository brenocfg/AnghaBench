#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {struct TYPE_3__* min_tb_addr_zs_tab; struct TYPE_3__* tile_id; struct TYPE_3__* tile_pos_rs; struct TYPE_3__* ctb_addr_ts_to_rs; struct TYPE_3__* ctb_addr_rs_to_ts; struct TYPE_3__* col_idxX; struct TYPE_3__* row_bd; struct TYPE_3__* col_bd; struct TYPE_3__* row_height; struct TYPE_3__* column_width; } ;
typedef  TYPE_1__ HEVCPPS ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 

__attribute__((used)) static void hevc_pps_free(void *opaque, uint8_t *data)
{
    HEVCPPS *pps = (HEVCPPS*)data;

    av_freep(&pps->column_width);
    av_freep(&pps->row_height);
    av_freep(&pps->col_bd);
    av_freep(&pps->row_bd);
    av_freep(&pps->col_idxX);
    av_freep(&pps->ctb_addr_rs_to_ts);
    av_freep(&pps->ctb_addr_ts_to_rs);
    av_freep(&pps->tile_pos_rs);
    av_freep(&pps->tile_id);
    av_freep(&pps->min_tb_addr_zs_tab);

    av_freep(&pps);
}