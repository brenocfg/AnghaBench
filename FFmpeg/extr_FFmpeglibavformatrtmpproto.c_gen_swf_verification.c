#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  URLContext ;
struct TYPE_8__ {int /*<<< orphan*/  swfverification; } ;
struct TYPE_7__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ RTMPPacket ;
typedef  TYPE_2__ RTMPContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  RTMP_NETWORK_CHANNEL ; 
 int /*<<< orphan*/  RTMP_PT_USER_CONTROL ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bytestream_put_be16 (int /*<<< orphan*/ **,int) ; 
 int ff_rtmp_packet_create (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int rtmp_send_packet (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gen_swf_verification(URLContext *s, RTMPContext *rt)
{
    RTMPPacket pkt;
    uint8_t *p;
    int ret;

    av_log(s, AV_LOG_DEBUG, "Sending SWF verification...\n");
    if ((ret = ff_rtmp_packet_create(&pkt, RTMP_NETWORK_CHANNEL, RTMP_PT_USER_CONTROL,
                                     0, 44)) < 0)
        return ret;

    p = pkt.data;
    bytestream_put_be16(&p, 27);
    memcpy(p, rt->swfverification, 42);

    return rtmp_send_packet(rt, &pkt, 0);
}