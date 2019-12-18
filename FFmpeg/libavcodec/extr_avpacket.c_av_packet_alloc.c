#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  av_init_packet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * av_mallocz (int) ; 

AVPacket *av_packet_alloc(void)
{
    AVPacket *pkt = av_mallocz(sizeof(AVPacket));
    if (!pkt)
        return pkt;

    av_init_packet(pkt);

    return pkt;
}