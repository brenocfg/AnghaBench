#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_4__ {int duration; int /*<<< orphan*/  dts; int /*<<< orphan*/  pts; } ;
typedef  int /*<<< orphan*/  FailingMuxerPacketData ;
typedef  TYPE_1__ AVPacket ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * av_malloc (int) ; 
 int av_packet_from_data (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int prepare_packet(AVPacket *pkt, const FailingMuxerPacketData *pkt_data, int64_t pts)
{
    int ret;
    FailingMuxerPacketData *data = av_malloc(sizeof(*data));
    if (!data) {
        return AVERROR(ENOMEM);
    }
    memcpy(data, pkt_data, sizeof(FailingMuxerPacketData));
    ret = av_packet_from_data(pkt, (uint8_t*) data, sizeof(*data));

    pkt->pts = pkt->dts = pts;
    pkt->duration = 1;

    return ret;
}