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
struct TYPE_8__ {int /*<<< orphan*/ * pb; } ;
struct TYPE_7__ {scalar_t__ stream_index; } ;
typedef  TYPE_1__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  TXD_EXTRA 131 
#define  TXD_FILE 130 
#define  TXD_INFO 129 
 unsigned int TXD_MARKER ; 
 unsigned int TXD_MARKER2 ; 
#define  TXD_TEXTURE 128 
 int av_get_packet (int /*<<< orphan*/ *,TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ *) ; 
 unsigned int avio_rl32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int txd_read_packet(AVFormatContext *s, AVPacket *pkt) {
    AVIOContext *pb = s->pb;
    unsigned int id, chunk_size, marker;
    int ret;

next_chunk:
    id         = avio_rl32(pb);
    chunk_size = avio_rl32(pb);
    marker     = avio_rl32(pb);

    if (avio_feof(s->pb))
        return AVERROR_EOF;
    if (marker != TXD_MARKER && marker != TXD_MARKER2) {
        av_log(s, AV_LOG_ERROR, "marker does not match\n");
        return AVERROR_INVALIDDATA;
    }

    switch (id) {
    case TXD_INFO:
        if (chunk_size > 100)
            break;
    case TXD_EXTRA:
        avio_skip(s->pb, chunk_size);
    case TXD_FILE:
    case TXD_TEXTURE:
        goto next_chunk;
    default:
        av_log(s, AV_LOG_ERROR, "unknown chunk id %i\n", id);
        return AVERROR_INVALIDDATA;
    }

    ret = av_get_packet(s->pb, pkt, chunk_size);
    if (ret < 0)
        return ret;
    pkt->stream_index = 0;

    return 0;
}