#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int size; int channel_id; int timestamp; scalar_t__ ts_field; scalar_t__ extra; int /*<<< orphan*/  type; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  RTMPPacketType ;
typedef  TYPE_1__ RTMPPacket ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_realloc (int /*<<< orphan*/ *,int) ; 

int ff_rtmp_packet_create(RTMPPacket *pkt, int channel_id, RTMPPacketType type,
                          int timestamp, int size)
{
    if (size) {
        pkt->data = av_realloc(NULL, size);
        if (!pkt->data)
            return AVERROR(ENOMEM);
    }
    pkt->size       = size;
    pkt->channel_id = channel_id;
    pkt->type       = type;
    pkt->timestamp  = timestamp;
    pkt->extra      = 0;
    pkt->ts_field   = 0;

    return 0;
}