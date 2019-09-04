#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* internal; } ;
struct TYPE_8__ {TYPE_1__* buffer_pkt; scalar_t__ eof; } ;
struct TYPE_7__ {int /*<<< orphan*/  side_data_elems; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVBSFInternal ;
typedef  TYPE_3__ AVBSFContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_1__* av_packet_alloc () ; 

int ff_bsf_get_packet(AVBSFContext *ctx, AVPacket **pkt)
{
    AVBSFInternal *in = ctx->internal;
    AVPacket *tmp_pkt;

    if (in->eof)
        return AVERROR_EOF;

    if (!ctx->internal->buffer_pkt->data &&
        !ctx->internal->buffer_pkt->side_data_elems)
        return AVERROR(EAGAIN);

    tmp_pkt = av_packet_alloc();
    if (!tmp_pkt)
        return AVERROR(ENOMEM);

    *pkt = ctx->internal->buffer_pkt;
    ctx->internal->buffer_pkt = tmp_pkt;

    return 0;
}