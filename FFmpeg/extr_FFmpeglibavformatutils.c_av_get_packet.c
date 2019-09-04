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
struct TYPE_5__ {int /*<<< orphan*/  pos; scalar_t__ size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int append_packet_chunked (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  av_init_packet (TYPE_1__*) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 

int av_get_packet(AVIOContext *s, AVPacket *pkt, int size)
{
    av_init_packet(pkt);
    pkt->data = NULL;
    pkt->size = 0;
    pkt->pos  = avio_tell(s);

    return append_packet_chunked(s, pkt, size);
}