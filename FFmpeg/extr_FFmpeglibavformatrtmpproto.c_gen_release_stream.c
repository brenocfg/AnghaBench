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
struct TYPE_8__ {char* playpath; int /*<<< orphan*/  nb_invokes; } ;
struct TYPE_7__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ RTMPPacket ;
typedef  TYPE_2__ RTMPContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  RTMP_PT_INVOKE ; 
 int /*<<< orphan*/  RTMP_SYSTEM_CHANNEL ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_amf_write_null (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_amf_write_number (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_amf_write_string (int /*<<< orphan*/ **,char*) ; 
 int ff_rtmp_packet_create (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int rtmp_send_packet (TYPE_2__*,TYPE_1__*,int) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int gen_release_stream(URLContext *s, RTMPContext *rt)
{
    RTMPPacket pkt;
    uint8_t *p;
    int ret;

    if ((ret = ff_rtmp_packet_create(&pkt, RTMP_SYSTEM_CHANNEL, RTMP_PT_INVOKE,
                                     0, 29 + strlen(rt->playpath))) < 0)
        return ret;

    av_log(s, AV_LOG_DEBUG, "Releasing stream...\n");
    p = pkt.data;
    ff_amf_write_string(&p, "releaseStream");
    ff_amf_write_number(&p, ++rt->nb_invokes);
    ff_amf_write_null(&p);
    ff_amf_write_string(&p, rt->playpath);

    return rtmp_send_packet(rt, &pkt, 1);
}