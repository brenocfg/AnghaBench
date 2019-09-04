#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* priv_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  queue_end; scalar_t__ queue; } ;
typedef  TYPE_1__ FlacMuxerContext ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_packet_list_get (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int flac_finish_header (TYPE_2__*) ; 
 int flac_write_audio_packet (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int flac_queue_flush(AVFormatContext *s)
{
    FlacMuxerContext *c = s->priv_data;
    AVPacket pkt;
    int ret, write = 1;

    ret = flac_finish_header(s);
    if (ret < 0)
        write = 0;

    while (c->queue) {
        ff_packet_list_get(&c->queue, &c->queue_end, &pkt);
        if (write && (ret = flac_write_audio_packet(s, &pkt)) < 0)
            write = 0;
        av_packet_unref(&pkt);
    }
    return ret;
}