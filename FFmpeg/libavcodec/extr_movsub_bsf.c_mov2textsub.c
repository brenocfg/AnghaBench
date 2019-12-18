#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int size; int data; } ;
typedef  TYPE_1__ AVPacket ;
typedef  int /*<<< orphan*/  AVBSFContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_RB16 (int) ; 
 int FFMIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_1__*) ; 
 int ff_bsf_get_packet_ref (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int mov2textsub(AVBSFContext *ctx, AVPacket *pkt)
{
    int ret = 0;

    ret = ff_bsf_get_packet_ref(ctx, pkt);
    if (ret < 0)
        return ret;

    if (pkt->size < 2) {
       av_packet_unref(pkt);
       return AVERROR_INVALIDDATA;
    }

    pkt->size  = FFMIN(pkt->size - 2, AV_RB16(pkt->data));
    pkt->data += 2;

    return 0;
}