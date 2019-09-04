#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pb; int /*<<< orphan*/  strict_compliance; TYPE_2__* avctx; } ;
typedef  TYPE_1__ VC2EncContext ;
struct TYPE_5__ {scalar_t__ color_primaries; scalar_t__ colorspace; scalar_t__ color_trc; } ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AVCOL_PRI_BT470BG ; 
 scalar_t__ AVCOL_PRI_SMPTE170M ; 
 scalar_t__ AVCOL_PRI_SMPTE240M ; 
 scalar_t__ AVCOL_SPC_BT470BG ; 
 scalar_t__ AVCOL_SPC_RGB ; 
 scalar_t__ AVCOL_SPC_YCOCG ; 
 scalar_t__ AVCOL_TRC_BT1361_ECG ; 
 scalar_t__ AVCOL_TRC_LINEAR ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  put_vc2_ue_uint (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void encode_color_spec(VC2EncContext *s)
{
    AVCodecContext *avctx = s->avctx;
    put_bits(&s->pb, 1, !s->strict_compliance);
    if (!s->strict_compliance) {
        int val;
        put_vc2_ue_uint(&s->pb, 0);

        /* primaries */
        put_bits(&s->pb, 1, 1);
        if (avctx->color_primaries == AVCOL_PRI_BT470BG)
            val = 2;
        else if (avctx->color_primaries == AVCOL_PRI_SMPTE170M)
            val = 1;
        else if (avctx->color_primaries == AVCOL_PRI_SMPTE240M)
            val = 1;
        else
            val = 0;
        put_vc2_ue_uint(&s->pb, val);

        /* color matrix */
        put_bits(&s->pb, 1, 1);
        if (avctx->colorspace == AVCOL_SPC_RGB)
            val = 3;
        else if (avctx->colorspace == AVCOL_SPC_YCOCG)
            val = 2;
        else if (avctx->colorspace == AVCOL_SPC_BT470BG)
            val = 1;
        else
            val = 0;
        put_vc2_ue_uint(&s->pb, val);

        /* transfer function */
        put_bits(&s->pb, 1, 1);
        if (avctx->color_trc == AVCOL_TRC_LINEAR)
            val = 2;
        else if (avctx->color_trc == AVCOL_TRC_BT1361_ECG)
            val = 1;
        else
            val = 0;
        put_vc2_ue_uint(&s->pb, val);
    }
}