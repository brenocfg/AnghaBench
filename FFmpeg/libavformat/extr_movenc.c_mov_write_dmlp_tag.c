#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_3__ {int vos_len; scalar_t__ vos_data; } ;
typedef  TYPE_1__ MOVTrack ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_RB16 (scalar_t__) ; 
 int AV_RB32 (scalar_t__) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_dmlp_tag(AVFormatContext *s, AVIOContext *pb, MOVTrack *track)
{
    int64_t pos = avio_tell(pb);
    int length;
    avio_wb32(pb, 0);
    ffio_wfourcc(pb, "dmlp");

    if (track->vos_len < 20) {
        av_log(s, AV_LOG_ERROR,
               "Cannot write moov atom before TrueHD packets."
               " Set the delay_moov flag to fix this.\n");
        return AVERROR(EINVAL);
    }

    length = (AV_RB16(track->vos_data) & 0xFFF) * 2;
    if (length < 20 || length > track->vos_len)
        return AVERROR_INVALIDDATA;

    // Only TrueHD is supported
    if (AV_RB32(track->vos_data + 4) != 0xF8726FBA)
        return AVERROR_INVALIDDATA;

    avio_wb32(pb, AV_RB32(track->vos_data + 8)); /* format_info */
    avio_wb16(pb, AV_RB16(track->vos_data + 18) << 1); /* peak_data_rate */
    avio_wb32(pb, 0); /* reserved */

    return update_size(pb, pos);
}