#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {scalar_t__ multichannel_as_mono; TYPE_1__* par; } ;
struct TYPE_4__ {int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  codec_id; } ;
typedef  TYPE_2__ MOVTrack ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb24 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_mov_get_channel_layout_tag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_chan_tag(AVFormatContext *s, AVIOContext *pb, MOVTrack *track)
{
    uint32_t layout_tag, bitmap;
    int64_t pos = avio_tell(pb);

    layout_tag = ff_mov_get_channel_layout_tag(track->par->codec_id,
                                               track->par->channel_layout,
                                               &bitmap);
    if (!layout_tag) {
        av_log(s, AV_LOG_WARNING, "not writing 'chan' tag due to "
               "lack of channel information\n");
        return 0;
    }

    if (track->multichannel_as_mono)
        return 0;

    avio_wb32(pb, 0);           // Size
    ffio_wfourcc(pb, "chan");   // Type
    avio_w8(pb, 0);             // Version
    avio_wb24(pb, 0);           // Flags
    avio_wb32(pb, layout_tag);  // mChannelLayoutTag
    avio_wb32(pb, bitmap);      // mChannelBitmap
    avio_wb32(pb, 0);           // mNumberChannelDescriptions

    return update_size(pb, pos);
}