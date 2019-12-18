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
typedef  int uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/ * pb; } ;
struct TYPE_6__ {int pos; int duration; } ;
typedef  TYPE_1__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  EIO ; 
 int av_get_packet (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ *) ; 
 int avio_rb32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int read_packet(AVFormatContext *s, AVPacket *pkt)
{
    AVIOContext *pb = s->pb;
    uint32_t chunk_size, payload_size;
    int ret;

    if (avio_feof(pb))
        return AVERROR_EOF;

    avio_skip(pb, 4);
    chunk_size = avio_rb32(pb);
    avio_skip(pb, 4);
    payload_size = avio_rb32(pb);

    if (chunk_size < payload_size + 16)
        return AVERROR(EIO);

    ret = av_get_packet(pb, pkt, payload_size);
    if (ret < 0)
        return ret;

    pkt->pos -= 16;
    pkt->duration = 1;
    avio_skip(pb, chunk_size - (ret + 16));

    return ret;
}