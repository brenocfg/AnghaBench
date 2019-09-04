#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  pb; } ;
struct TYPE_9__ {int pts; int pos; scalar_t__ stream_index; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PKT_FLAG_CORRUPT ; 
 int av_append_packet (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int av_get_packet (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_1__*) ; 
 int avio_rb16 (int /*<<< orphan*/ ) ; 
 int avio_rb32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int read_packet(AVFormatContext *s, AVPacket *pkt)
{
    int ret, size, pts, type, flags;
    int first_pkt      = 0;
    int frame_complete = 0;

    while (!frame_complete) {

        type  = avio_rb16(s->pb); // 257 or 258
        size  = avio_rb16(s->pb);
        flags = avio_rb16(s->pb); //some flags, 0x80 indicates end of frame
                avio_rb16(s->pb); //packet number
        pts   = avio_rb32(s->pb);
                avio_rb32(s->pb); //6A 13 E3 88

        frame_complete = flags & 0x80;

        size -= 12;
        if (size < 1)
            return -1;

        if (type == 258) {
            avio_skip(s->pb, size);
            frame_complete = 0;
            continue;
        }

        if (!first_pkt) {
            ret = av_get_packet(s->pb, pkt, size);
            if (ret < 0)
                return ret;
            first_pkt = 1;
            pkt->pts  = pts;
            pkt->pos -= 16;
        } else {
            ret = av_append_packet(s->pb, pkt, size);
            if (ret < 0) {
                av_log(s, AV_LOG_ERROR, "failed to grow packet\n");
                av_packet_unref(pkt);
                return ret;
            }
        }
        if (ret < size) {
            av_log(s, AV_LOG_ERROR, "Truncated packet! Read %d of %d bytes\n",
                   ret, size);
            pkt->flags |= AV_PKT_FLAG_CORRUPT;
            break;
        }
    }
    pkt->stream_index = 0;

    return 0;
}