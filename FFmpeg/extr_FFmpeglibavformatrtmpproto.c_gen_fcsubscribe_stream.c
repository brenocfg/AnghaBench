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
struct TYPE_8__ {int /*<<< orphan*/  nb_invokes; } ;
struct TYPE_7__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ RTMPPacket ;
typedef  TYPE_2__ RTMPContext ;

/* Variables and functions */
 int /*<<< orphan*/  RTMP_PT_INVOKE ; 
 int /*<<< orphan*/  RTMP_SYSTEM_CHANNEL ; 
 int /*<<< orphan*/  ff_amf_write_null (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_amf_write_number (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_amf_write_string (int /*<<< orphan*/ **,char const*) ; 
 int ff_rtmp_packet_create (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int rtmp_send_packet (TYPE_2__*,TYPE_1__*,int) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int gen_fcsubscribe_stream(URLContext *s, RTMPContext *rt,
                                  const char *subscribe)
{
    RTMPPacket pkt;
    uint8_t *p;
    int ret;

    if ((ret = ff_rtmp_packet_create(&pkt, RTMP_SYSTEM_CHANNEL, RTMP_PT_INVOKE,
                                     0, 27 + strlen(subscribe))) < 0)
        return ret;

    p = pkt.data;
    ff_amf_write_string(&p, "FCSubscribe");
    ff_amf_write_number(&p, ++rt->nb_invokes);
    ff_amf_write_null(&p);
    ff_amf_write_string(&p, subscribe);

    return rtmp_send_packet(rt, &pkt, 1);
}