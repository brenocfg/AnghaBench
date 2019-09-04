#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_8__ {scalar_t__ data_offset; int data_size; scalar_t__ pts; scalar_t__ last_pts; int /*<<< orphan*/  stream_index; } ;
typedef  TYPE_1__ XMVVideoPacket ;
struct TYPE_9__ {TYPE_1__ video; } ;
typedef  TYPE_2__ XMVDemuxContext ;
struct TYPE_11__ {int /*<<< orphan*/ * pb; TYPE_2__* priv_data; } ;
struct TYPE_10__ {int* data; int /*<<< orphan*/  flags; int /*<<< orphan*/  dts; scalar_t__ pts; scalar_t__ duration; int /*<<< orphan*/  stream_index; } ;
typedef  TYPE_3__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  AV_RL32 (int*) ; 
 int /*<<< orphan*/  AV_WB32 (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int av_get_packet (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int avio_rl32 (int /*<<< orphan*/ *) ; 
 scalar_t__ avio_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xmv_fetch_video_packet(AVFormatContext *s,
                                  AVPacket *pkt)
{
    XMVDemuxContext *xmv   = s->priv_data;
    AVIOContext     *pb    = s->pb;
    XMVVideoPacket  *video = &xmv->video;

    int result;
    uint32_t frame_header;
    uint32_t frame_size, frame_timestamp;
    uint8_t *data, *end;

    /* Seek to it */
    if (avio_seek(pb, video->data_offset, SEEK_SET) != video->data_offset)
        return AVERROR(EIO);

    /* Read the frame header */
    frame_header = avio_rl32(pb);

    frame_size      = (frame_header & 0x1FFFF) * 4 + 4;
    frame_timestamp = (frame_header >> 17);

    if ((frame_size + 4) > video->data_size)
        return AVERROR(EIO);

    /* Get the packet data */
    result = av_get_packet(pb, pkt, frame_size);
    if (result != frame_size)
        return result;

    /* Contrary to normal WMV2 video, the bit stream in XMV's
     * WMV2 is little-endian.
     * TODO: This manual swap is of course suboptimal.
     */
    for (data = pkt->data, end = pkt->data + frame_size; data < end; data += 4)
        AV_WB32(data, AV_RL32(data));

    pkt->stream_index = video->stream_index;

    /* Calculate the PTS */

    video->last_pts = frame_timestamp + video->pts;

    pkt->duration = 0;
    pkt->pts      = video->last_pts;
    pkt->dts      = AV_NOPTS_VALUE;

    video->pts += frame_timestamp;

    /* Keyframe? */
    pkt->flags = (pkt->data[0] & 0x80) ? 0 : AV_PKT_FLAG_KEY;

    /* Advance offset */
    video->data_size   -= frame_size + 4;
    video->data_offset += frame_size + 4;

    return 0;
}