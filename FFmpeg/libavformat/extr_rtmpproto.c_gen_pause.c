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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  URLContext ;
struct TYPE_8__ {int /*<<< orphan*/  stream_id; } ;
struct TYPE_7__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  extra; } ;
typedef  TYPE_1__ RTMPPacket ;
typedef  TYPE_2__ RTMPContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  RTMP_PT_INVOKE ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_amf_write_bool (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  ff_amf_write_null (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_amf_write_number (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_amf_write_string (int /*<<< orphan*/ **,char*) ; 
 int ff_rtmp_packet_create (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int rtmp_send_packet (TYPE_2__*,TYPE_1__*,int) ; 

__attribute__((used)) static int gen_pause(URLContext *s, RTMPContext *rt, int pause, uint32_t timestamp)
{
    RTMPPacket pkt;
    uint8_t *p;
    int ret;

    av_log(s, AV_LOG_DEBUG, "Sending pause command for timestamp %d\n",
           timestamp);

    if ((ret = ff_rtmp_packet_create(&pkt, 3, RTMP_PT_INVOKE, 0, 29)) < 0)
        return ret;

    pkt.extra = rt->stream_id;

    p = pkt.data;
    ff_amf_write_string(&p, "pause");
    ff_amf_write_number(&p, 0); //no tracking back responses
    ff_amf_write_null(&p); //as usual, the first null param
    ff_amf_write_bool(&p, pause); // pause or unpause
    ff_amf_write_number(&p, timestamp); //where we pause the stream

    return rtmp_send_packet(rt, &pkt, 1);
}