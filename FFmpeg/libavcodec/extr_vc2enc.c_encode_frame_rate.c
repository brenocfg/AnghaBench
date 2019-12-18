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
struct TYPE_6__ {int /*<<< orphan*/  pb; TYPE_3__* avctx; int /*<<< orphan*/  strict_compliance; } ;
typedef  TYPE_2__ VC2EncContext ;
struct TYPE_5__ {int /*<<< orphan*/  num; int /*<<< orphan*/  den; } ;
struct TYPE_7__ {TYPE_1__ time_base; } ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  put_vc2_ue_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encode_frame_rate(VC2EncContext *s)
{
    put_bits(&s->pb, 1, !s->strict_compliance);
    if (!s->strict_compliance) {
        AVCodecContext *avctx = s->avctx;
        put_vc2_ue_uint(&s->pb, 0);
        put_vc2_ue_uint(&s->pb, avctx->time_base.den);
        put_vc2_ue_uint(&s->pb, avctx->time_base.num);
    }
}