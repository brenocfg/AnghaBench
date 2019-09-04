#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_12__ {int /*<<< orphan*/  pb; TYPE_2__* priv_data; } ;
struct TYPE_11__ {int* data; int size; int /*<<< orphan*/  flags; int /*<<< orphan*/  stream_index; } ;
struct TYPE_10__ {TYPE_1__* st_video; } ;
struct TYPE_9__ {int /*<<< orphan*/  index; } ;
typedef  TYPE_2__ AvsFormat ;
typedef  int AvsBlockType ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  EIO ; 
 int av_new_packet (TYPE_3__*,int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_3__*) ; 
 int avio_read (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
avs_read_video_packet(AVFormatContext * s, AVPacket * pkt,
                      AvsBlockType type, int sub_type, int size,
                      uint8_t * palette, int palette_size)
{
    AvsFormat *avs = s->priv_data;
    int ret;

    ret = av_new_packet(pkt, size + palette_size);
    if (ret < 0)
        return ret;

    if (palette_size) {
        pkt->data[0] = 0x00;
        pkt->data[1] = 0x03;
        pkt->data[2] = palette_size & 0xFF;
        pkt->data[3] = (palette_size >> 8) & 0xFF;
        memcpy(pkt->data + 4, palette, palette_size - 4);
    }

    pkt->data[palette_size + 0] = sub_type;
    pkt->data[palette_size + 1] = type;
    pkt->data[palette_size + 2] = size & 0xFF;
    pkt->data[palette_size + 3] = (size >> 8) & 0xFF;
    ret = avio_read(s->pb, pkt->data + palette_size + 4, size - 4) + 4;
    if (ret < size) {
        av_packet_unref(pkt);
        return AVERROR(EIO);
    }

    pkt->size = ret + palette_size;
    pkt->stream_index = avs->st_video->index;
    if (sub_type == 0)
        pkt->flags |= AV_PKT_FLAG_KEY;

    return 0;
}