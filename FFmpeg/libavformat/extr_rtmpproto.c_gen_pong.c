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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  URLContext ;
struct TYPE_5__ {int size; int /*<<< orphan*/ * data; scalar_t__ timestamp; } ;
typedef  TYPE_1__ RTMPPacket ;
typedef  int /*<<< orphan*/  RTMPContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_RB32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RTMP_NETWORK_CHANNEL ; 
 int /*<<< orphan*/  RTMP_PT_USER_CONTROL ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  bytestream_put_be16 (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  bytestream_put_be32 (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int ff_rtmp_packet_create (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int rtmp_send_packet (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gen_pong(URLContext *s, RTMPContext *rt, RTMPPacket *ppkt)
{
    RTMPPacket pkt;
    uint8_t *p;
    int ret;

    if (ppkt->size < 6) {
        av_log(s, AV_LOG_ERROR, "Too short ping packet (%d)\n",
               ppkt->size);
        return AVERROR_INVALIDDATA;
    }

    if ((ret = ff_rtmp_packet_create(&pkt, RTMP_NETWORK_CHANNEL,RTMP_PT_USER_CONTROL,
                                     ppkt->timestamp + 1, 6)) < 0)
        return ret;

    p = pkt.data;
    bytestream_put_be16(&p, 7); // PingResponse
    bytestream_put_be32(&p, AV_RB32(ppkt->data+2));

    return rtmp_send_packet(rt, &pkt, 0);
}