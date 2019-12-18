#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ side_data_elems; scalar_t__ data; } ;
struct TYPE_12__ {TYPE_1__* internal; } ;
struct TYPE_11__ {int /*<<< orphan*/  side_data_elems; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {int eof; TYPE_4__* buffer_pkt; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVBSFContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int av_packet_make_refcounted (TYPE_2__*) ; 
 int /*<<< orphan*/  av_packet_move_ref (TYPE_4__*,TYPE_2__*) ; 

int av_bsf_send_packet(AVBSFContext *ctx, AVPacket *pkt)
{
    int ret;

    if (!pkt || (!pkt->data && !pkt->side_data_elems)) {
        ctx->internal->eof = 1;
        return 0;
    }

    if (ctx->internal->eof) {
        av_log(ctx, AV_LOG_ERROR, "A non-NULL packet sent after an EOF.\n");
        return AVERROR(EINVAL);
    }

    if (ctx->internal->buffer_pkt->data ||
        ctx->internal->buffer_pkt->side_data_elems)
        return AVERROR(EAGAIN);

    ret = av_packet_make_refcounted(pkt);
    if (ret < 0)
        return ret;
    av_packet_move_ref(ctx->internal->buffer_pkt, pkt);

    return 0;
}