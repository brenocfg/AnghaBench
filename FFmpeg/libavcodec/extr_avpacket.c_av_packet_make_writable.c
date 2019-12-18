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
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; TYPE_2__* buf; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVBufferRef ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert1 (int) ; 
 scalar_t__ av_buffer_is_writable (TYPE_2__*) ; 
 int /*<<< orphan*/  av_buffer_unref (TYPE_2__**) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int packet_alloc (TYPE_2__**,int /*<<< orphan*/ ) ; 

int av_packet_make_writable(AVPacket *pkt)
{
    AVBufferRef *buf = NULL;
    int ret;

    if (pkt->buf && av_buffer_is_writable(pkt->buf))
        return 0;

    ret = packet_alloc(&buf, pkt->size);
    if (ret < 0)
        return ret;
    av_assert1(!pkt->size || pkt->data);
    if (pkt->size)
        memcpy(buf->data, pkt->data, pkt->size);

    av_buffer_unref(&pkt->buf);
    pkt->buf  = buf;
    pkt->data = buf->data;

    return 0;
}