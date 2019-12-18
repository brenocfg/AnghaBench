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
struct TYPE_3__ {int /*<<< orphan*/  avpkt; scalar_t__ duration; scalar_t__ dts; scalar_t__ flags; scalar_t__ data_size; scalar_t__ size_left; } ;
typedef  TYPE_1__ ASFPacket ;

/* Variables and functions */
 int /*<<< orphan*/  av_init_packet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reset_packet(ASFPacket *asf_pkt)
{
    asf_pkt->size_left = 0;
    asf_pkt->data_size = 0;
    asf_pkt->duration  = 0;
    asf_pkt->flags     = 0;
    asf_pkt->dts       = 0;
    asf_pkt->duration  = 0;
    av_packet_unref(&asf_pkt->avpkt);
    av_init_packet(&asf_pkt->avpkt);
}