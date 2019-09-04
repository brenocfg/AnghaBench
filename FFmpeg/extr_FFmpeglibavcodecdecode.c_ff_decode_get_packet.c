#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_1__* codec; TYPE_3__* internal; } ;
struct TYPE_16__ {int draining; int /*<<< orphan*/  compat_decode_consumed; } ;
struct TYPE_15__ {scalar_t__ size; } ;
struct TYPE_14__ {scalar_t__ receive_frame; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVCodecInternal ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int apply_param_change (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_2__*) ; 
 int bsfs_poll (TYPE_4__*,TYPE_2__*) ; 
 int extract_packet_props (TYPE_3__*,TYPE_2__*) ; 

int ff_decode_get_packet(AVCodecContext *avctx, AVPacket *pkt)
{
    AVCodecInternal *avci = avctx->internal;
    int ret;

    if (avci->draining)
        return AVERROR_EOF;

    ret = bsfs_poll(avctx, pkt);
    if (ret == AVERROR_EOF)
        avci->draining = 1;
    if (ret < 0)
        return ret;

    ret = extract_packet_props(avctx->internal, pkt);
    if (ret < 0)
        goto finish;

    ret = apply_param_change(avctx, pkt);
    if (ret < 0)
        goto finish;

    if (avctx->codec->receive_frame)
        avci->compat_decode_consumed += pkt->size;

    return 0;
finish:
    av_packet_unref(pkt);
    return ret;
}