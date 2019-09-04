#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_14__ {int error; scalar_t__ eof_reached; } ;
struct TYPE_13__ {int packet_size; TYPE_1__* internal; TYPE_6__* pb; } ;
struct TYPE_12__ {int pts; int duration; scalar_t__ stream_index; } ;
struct TYPE_11__ {int data_offset; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  EIO ; 
 int MAX_FRAME_HEADER ; 
 int /*<<< orphan*/  Y4M_FRAME_MAGIC ; 
 int Y4M_FRAME_MAGIC_LEN ; 
 int av_get_packet (TYPE_6__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_2__*) ; 
 char avio_r8 (TYPE_6__*) ; 
 int avio_tell (TYPE_6__*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int yuv4_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    int i;
    char header[MAX_FRAME_HEADER+1];
    int ret;
    int64_t off = avio_tell(s->pb);

    for (i = 0; i < MAX_FRAME_HEADER; i++) {
        header[i] = avio_r8(s->pb);
        if (header[i] == '\n') {
            header[i + 1] = 0;
            break;
        }
    }
    if (s->pb->error)
        return s->pb->error;
    else if (s->pb->eof_reached)
        return AVERROR_EOF;
    else if (i == MAX_FRAME_HEADER)
        return AVERROR_INVALIDDATA;

    if (strncmp(header, Y4M_FRAME_MAGIC, strlen(Y4M_FRAME_MAGIC)))
        return AVERROR_INVALIDDATA;

    ret = av_get_packet(s->pb, pkt, s->packet_size - Y4M_FRAME_MAGIC_LEN);
    if (ret < 0)
        return ret;
    else if (ret != s->packet_size - Y4M_FRAME_MAGIC_LEN) {
        av_packet_unref(pkt);
        return s->pb->eof_reached ? AVERROR_EOF : AVERROR(EIO);
    }
    pkt->stream_index = 0;
    pkt->pts = (off - s->internal->data_offset) / s->packet_size;
    pkt->duration = 1;
    return 0;
}