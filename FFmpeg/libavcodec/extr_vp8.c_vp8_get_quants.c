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
struct TYPE_7__ {int yac_qi; int ydc_delta; int y2dc_delta; int y2ac_delta; int uvdc_delta; int uvac_delta; } ;
struct TYPE_6__ {int* base_quant; int /*<<< orphan*/  absolute_vals; scalar_t__ enabled; } ;
struct TYPE_9__ {TYPE_3__* qmat; TYPE_2__ quant; TYPE_1__ segmentation; int /*<<< orphan*/  c; } ;
typedef  TYPE_4__ VP8Context ;
typedef  int /*<<< orphan*/  VP56RangeCoder ;
struct TYPE_8__ {int* luma_qmul; int* luma_dc_qmul; int* chroma_qmul; } ;

/* Variables and functions */
 int FFMAX (int,int) ; 
 int FFMIN (int,int) ; 
 size_t av_clip_uintp2 (int,int) ; 
 int* vp8_ac_qlookup ; 
 int* vp8_dc_qlookup ; 
 void* vp8_rac_get_sint (int /*<<< orphan*/ *,int) ; 
 int vp8_rac_get_uint (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void vp8_get_quants(VP8Context *s)
{
    VP56RangeCoder *c = &s->c;
    int i, base_qi;

    s->quant.yac_qi     = vp8_rac_get_uint(c, 7);
    s->quant.ydc_delta  = vp8_rac_get_sint(c, 4);
    s->quant.y2dc_delta = vp8_rac_get_sint(c, 4);
    s->quant.y2ac_delta = vp8_rac_get_sint(c, 4);
    s->quant.uvdc_delta = vp8_rac_get_sint(c, 4);
    s->quant.uvac_delta = vp8_rac_get_sint(c, 4);

    for (i = 0; i < 4; i++) {
        if (s->segmentation.enabled) {
            base_qi = s->segmentation.base_quant[i];
            if (!s->segmentation.absolute_vals)
                base_qi += s->quant.yac_qi;
        } else
            base_qi = s->quant.yac_qi;

        s->qmat[i].luma_qmul[0]    = vp8_dc_qlookup[av_clip_uintp2(base_qi + s->quant.ydc_delta,  7)];
        s->qmat[i].luma_qmul[1]    = vp8_ac_qlookup[av_clip_uintp2(base_qi,              7)];
        s->qmat[i].luma_dc_qmul[0] = vp8_dc_qlookup[av_clip_uintp2(base_qi + s->quant.y2dc_delta, 7)] * 2;
        /* 101581>>16 is equivalent to 155/100 */
        s->qmat[i].luma_dc_qmul[1] = vp8_ac_qlookup[av_clip_uintp2(base_qi + s->quant.y2ac_delta, 7)] * 101581 >> 16;
        s->qmat[i].chroma_qmul[0]  = vp8_dc_qlookup[av_clip_uintp2(base_qi + s->quant.uvdc_delta, 7)];
        s->qmat[i].chroma_qmul[1]  = vp8_ac_qlookup[av_clip_uintp2(base_qi + s->quant.uvac_delta, 7)];

        s->qmat[i].luma_dc_qmul[1] = FFMAX(s->qmat[i].luma_dc_qmul[1], 8);
        s->qmat[i].chroma_qmul[0]  = FFMIN(s->qmat[i].chroma_qmul[0], 132);
    }
}