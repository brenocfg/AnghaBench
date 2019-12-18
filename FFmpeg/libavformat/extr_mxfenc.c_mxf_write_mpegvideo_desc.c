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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_12__ {int /*<<< orphan*/ * pb; } ;
struct TYPE_11__ {TYPE_1__* codecpar; TYPE_2__* priv_data; } ;
struct TYPE_10__ {int low_delay; int seq_closed_gop; int /*<<< orphan*/  b_picture_count; int /*<<< orphan*/  max_gop; int /*<<< orphan*/  video_bit_rate; } ;
struct TYPE_9__ {int profile; int level; scalar_t__ codec_id; } ;
typedef  TYPE_2__ MXFStreamContext ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_H264 ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxf_mpegvideo_descriptor_key ; 
 int /*<<< orphan*/  mxf_update_klv_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxf_write_cdci_common (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxf_write_local_tag (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void mxf_write_mpegvideo_desc(AVFormatContext *s, AVStream *st)
{
    AVIOContext *pb = s->pb;
    MXFStreamContext *sc = st->priv_data;
    int profile_and_level = (st->codecpar->profile<<4) | st->codecpar->level;
    int64_t pos = mxf_write_cdci_common(s, st, mxf_mpegvideo_descriptor_key);

    if (st->codecpar->codec_id != AV_CODEC_ID_H264) {
        // bit rate
        mxf_write_local_tag(pb, 4, 0x8000);
        avio_wb32(pb, sc->video_bit_rate);

        // profile and level
        mxf_write_local_tag(pb, 1, 0x8007);
        if (!st->codecpar->profile)
            profile_and_level |= 0x80; // escape bit
        avio_w8(pb, profile_and_level);

        // low delay
        mxf_write_local_tag(pb, 1, 0x8003);
        avio_w8(pb, sc->low_delay);

        // closed gop
        mxf_write_local_tag(pb, 1, 0x8004);
        avio_w8(pb, sc->seq_closed_gop);

        // max gop
        mxf_write_local_tag(pb, 2, 0x8006);
        avio_wb16(pb, sc->max_gop);

        // b picture count
        mxf_write_local_tag(pb, 2, 0x8008);
        avio_wb16(pb, sc->b_picture_count);
    }

    mxf_update_klv_size(pb, pos);
}