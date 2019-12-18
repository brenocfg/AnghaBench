#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ptrdiff_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* edge_filter_ver ) (int /*<<< orphan*/ *,int,int) ;int /*<<< orphan*/  (* edge_filter_hor ) (int /*<<< orphan*/ *,int,int) ;} ;
struct TYPE_9__ {size_t quantizer; int* bounding_values_array; TYPE_1__ vp56dsp; TYPE_2__* avctx; } ;
typedef  TYPE_4__ VP56Context ;
struct TYPE_8__ {scalar_t__ id; } ;
struct TYPE_7__ {TYPE_3__* codec; } ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_VP5 ; 
 int /*<<< orphan*/  ff_vp3dsp_h_loop_filter_12 (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  ff_vp3dsp_v_loop_filter_12 (int /*<<< orphan*/ *,int,int*) ; 
 int* ff_vp56_filter_threshold ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void vp56_deblock_filter(VP56Context *s, uint8_t *yuv,
                                ptrdiff_t stride, int dx, int dy)
{
    if (s->avctx->codec->id == AV_CODEC_ID_VP5) {
    int t = ff_vp56_filter_threshold[s->quantizer];
    if (dx)  s->vp56dsp.edge_filter_hor(yuv +         10-dx , stride, t);
    if (dy)  s->vp56dsp.edge_filter_ver(yuv + stride*(10-dy), stride, t);
    } else {
        int * bounding_values = s->bounding_values_array + 127;
        if (dx)
            ff_vp3dsp_h_loop_filter_12(yuv +         10-dx, stride, bounding_values);
        if (dy)
            ff_vp3dsp_v_loop_filter_12(yuv + stride*(10-dy), stride, bounding_values);
    }
}