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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {TYPE_1__* par; } ;
struct TYPE_4__ {int extradata_size; scalar_t__ extradata; } ;
typedef  TYPE_2__ MOVTrack ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_RB8 (scalar_t__) ; 
 int /*<<< orphan*/  AV_RL16 (scalar_t__) ; 
 int /*<<< orphan*/  AV_RL32 (scalar_t__) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_dops_tag(AVFormatContext *s, AVIOContext *pb, MOVTrack *track)
{
    int64_t pos = avio_tell(pb);
    avio_wb32(pb, 0);
    ffio_wfourcc(pb, "dOps");
    avio_w8(pb, 0); /* Version */
    if (track->par->extradata_size < 19) {
        av_log(s, AV_LOG_ERROR, "invalid extradata size\n");
        return AVERROR_INVALIDDATA;
    }
    /* extradata contains an Ogg OpusHead, other than byte-ordering and
       OpusHead's preceeding magic/version, OpusSpecificBox is currently
       identical. */
    avio_w8(pb, AV_RB8(track->par->extradata + 9)); /* OuputChannelCount */
    avio_wb16(pb, AV_RL16(track->par->extradata + 10)); /* PreSkip */
    avio_wb32(pb, AV_RL32(track->par->extradata + 12)); /* InputSampleRate */
    avio_wb16(pb, AV_RL16(track->par->extradata + 16)); /* OutputGain */
    /* Write the rest of the header out without byte-swapping. */
    avio_write(pb, track->par->extradata + 18, track->par->extradata_size - 18);

    return update_size(pb, pos);
}