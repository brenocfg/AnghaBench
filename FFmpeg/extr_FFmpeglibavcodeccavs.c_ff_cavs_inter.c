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
typedef  enum cavs_mb { ____Placeholder_cavs_mb } cavs_mb ;
struct TYPE_7__ {int /*<<< orphan*/ * avg_h264_chroma_pixels_tab; int /*<<< orphan*/ * put_h264_chroma_pixels_tab; } ;
struct TYPE_6__ {int /*<<< orphan*/ * avg_cavs_qpel_pixels_tab; int /*<<< orphan*/ * put_cavs_qpel_pixels_tab; } ;
struct TYPE_8__ {int /*<<< orphan*/ * mv; TYPE_2__ h264chroma; TYPE_1__ cdsp; int /*<<< orphan*/  cv; int /*<<< orphan*/  cu; int /*<<< orphan*/  cy; } ;
typedef  TYPE_3__ AVSContext ;

/* Variables and functions */
 size_t MV_FWD_X0 ; 
 size_t MV_FWD_X1 ; 
 size_t MV_FWD_X2 ; 
 size_t MV_FWD_X3 ; 
 scalar_t__* ff_cavs_partition_flags ; 
 int /*<<< orphan*/  mc_part_std (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ff_cavs_inter(AVSContext *h, enum cavs_mb mb_type)
{
    if (ff_cavs_partition_flags[mb_type] == 0) { // 16x16
        mc_part_std(h, 8, 0, h->cy, h->cu, h->cv, 0, 0,
                    h->cdsp.put_cavs_qpel_pixels_tab[0],
                    h->h264chroma.put_h264_chroma_pixels_tab[0],
                    h->cdsp.avg_cavs_qpel_pixels_tab[0],
                    h->h264chroma.avg_h264_chroma_pixels_tab[0],
                    &h->mv[MV_FWD_X0]);
    } else {
        mc_part_std(h, 4, 0, h->cy, h->cu, h->cv, 0, 0,
                    h->cdsp.put_cavs_qpel_pixels_tab[1],
                    h->h264chroma.put_h264_chroma_pixels_tab[1],
                    h->cdsp.avg_cavs_qpel_pixels_tab[1],
                    h->h264chroma.avg_h264_chroma_pixels_tab[1],
                    &h->mv[MV_FWD_X0]);
        mc_part_std(h, 4, 0, h->cy, h->cu, h->cv, 4, 0,
                    h->cdsp.put_cavs_qpel_pixels_tab[1],
                    h->h264chroma.put_h264_chroma_pixels_tab[1],
                    h->cdsp.avg_cavs_qpel_pixels_tab[1],
                    h->h264chroma.avg_h264_chroma_pixels_tab[1],
                    &h->mv[MV_FWD_X1]);
        mc_part_std(h, 4, 0, h->cy, h->cu, h->cv, 0, 4,
                    h->cdsp.put_cavs_qpel_pixels_tab[1],
                    h->h264chroma.put_h264_chroma_pixels_tab[1],
                    h->cdsp.avg_cavs_qpel_pixels_tab[1],
                    h->h264chroma.avg_h264_chroma_pixels_tab[1],
                    &h->mv[MV_FWD_X2]);
        mc_part_std(h, 4, 0, h->cy, h->cu, h->cv, 4, 4,
                    h->cdsp.put_cavs_qpel_pixels_tab[1],
                    h->h264chroma.put_h264_chroma_pixels_tab[1],
                    h->cdsp.avg_cavs_qpel_pixels_tab[1],
                    h->h264chroma.avg_h264_chroma_pixels_tab[1],
                    &h->mv[MV_FWD_X3]);
    }
}