#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_3__* priv_data; } ;
struct TYPE_13__ {int flags; int data; int size; } ;
struct TYPE_12__ {scalar_t__ freq; int /*<<< orphan*/  avctx; TYPE_2__* parser; } ;
struct TYPE_11__ {TYPE_1__* parser; } ;
struct TYPE_10__ {int (* split ) (int /*<<< orphan*/ ,int,int) ;} ;
typedef  TYPE_3__ RemoveExtradataContext ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVBSFContext ;

/* Variables and functions */
 int AV_PKT_FLAG_KEY ; 
 scalar_t__ REMOVE_FREQ_ALL ; 
 scalar_t__ REMOVE_FREQ_KEYFRAME ; 
 scalar_t__ REMOVE_FREQ_NONKEYFRAME ; 
 int ff_bsf_get_packet_ref (TYPE_5__*,TYPE_4__*) ; 
 int stub1 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int remove_extradata(AVBSFContext *ctx, AVPacket *pkt)
{
    RemoveExtradataContext *s = ctx->priv_data;

    int ret;

    ret = ff_bsf_get_packet_ref(ctx, pkt);
    if (ret < 0)
        return ret;

    if (s->parser && s->parser->parser->split) {
        if (s->freq == REMOVE_FREQ_ALL ||
            (s->freq == REMOVE_FREQ_NONKEYFRAME && !(pkt->flags & AV_PKT_FLAG_KEY)) ||
            (s->freq == REMOVE_FREQ_KEYFRAME && pkt->flags & AV_PKT_FLAG_KEY)) {
            int i = s->parser->parser->split(s->avctx, pkt->data, pkt->size);
            pkt->data += i;
            pkt->size -= i;
        }
    }

    return 0;
}