#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  side_data_elems; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {TYPE_1__* internal; } ;
struct TYPE_5__ {TYPE_4__* buffer_pkt; scalar_t__ eof; } ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_1__ AVBSFInternal ;
typedef  TYPE_2__ AVBSFContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  av_packet_move_ref (int /*<<< orphan*/ *,TYPE_4__*) ; 

int ff_bsf_get_packet_ref(AVBSFContext *ctx, AVPacket *pkt)
{
    AVBSFInternal *in = ctx->internal;

    if (in->eof)
        return AVERROR_EOF;

    if (!ctx->internal->buffer_pkt->data &&
        !ctx->internal->buffer_pkt->side_data_elems)
        return AVERROR(EAGAIN);

    av_packet_move_ref(pkt, ctx->internal->buffer_pkt);

    return 0;
}