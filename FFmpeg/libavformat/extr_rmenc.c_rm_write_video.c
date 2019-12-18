#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {int /*<<< orphan*/ * pb; TYPE_2__* priv_data; } ;
struct TYPE_9__ {TYPE_1__* video_stream; } ;
struct TYPE_8__ {int nb_frames; } ;
typedef  TYPE_1__ StreamInfo ;
typedef  TYPE_2__ RMMuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_PKT_FLAG_KEY ; 
 int MAX_PACKET_SIZE ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  write_packet_header (TYPE_3__*,TYPE_1__*,int,int) ; 

__attribute__((used)) static int rm_write_video(AVFormatContext *s, const uint8_t *buf, int size, int flags)
{
    RMMuxContext *rm = s->priv_data;
    AVIOContext *pb = s->pb;
    StreamInfo *stream = rm->video_stream;
    int key_frame = !!(flags & AV_PKT_FLAG_KEY);

    /* XXX: this is incorrect: should be a parameter */

    /* Well, I spent some time finding the meaning of these bits. I am
       not sure I understood everything, but it works !! */
    if (size > MAX_PACKET_SIZE) {
        av_log(s, AV_LOG_ERROR, "Muxing packets larger than 64 kB (%d) is not supported\n", size);
        return AVERROR_PATCHWELCOME;
    }
    write_packet_header(s, stream, size + 7 + (size >= 0x4000)*4, key_frame);
    /* bit 7: '1' if final packet of a frame converted in several packets */
    avio_w8(pb, 0x81);
    /* bit 7: '1' if I-frame. bits 6..0 : sequence number in current
       frame starting from 1 */
    if (key_frame) {
        avio_w8(pb, 0x81);
    } else {
        avio_w8(pb, 0x01);
    }
    if(size >= 0x4000){
        avio_wb32(pb, size); /* total frame size */
        avio_wb32(pb, size); /* offset from the start or the end */
    }else{
        avio_wb16(pb, 0x4000 | size); /* total frame size */
        avio_wb16(pb, 0x4000 | size); /* offset from the start or the end */
    }
    avio_w8(pb, stream->nb_frames & 0xff);

    avio_write(pb, buf, size);

    stream->nb_frames++;
    return 0;
}