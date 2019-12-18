#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_9__ {scalar_t__ write_prft; int /*<<< orphan*/  fc; TYPE_3__* tracks; } ;
struct TYPE_8__ {TYPE_2__* cluster; int /*<<< orphan*/  track_id; TYPE_1__* st; int /*<<< orphan*/  entry; } ;
struct TYPE_7__ {scalar_t__ pts; } ;
struct TYPE_6__ {int /*<<< orphan*/  time_base; } ;
typedef  TYPE_3__ MOVTrack ;
typedef  TYPE_4__ MOVMuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 scalar_t__ MOV_PRFT_SRC_PTS ; 
 scalar_t__ MOV_PRFT_SRC_WALLCLOCK ; 
 scalar_t__ NTP_OFFSET_US ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ av_rescale_q (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb24 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb64 (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ff_get_formatted_ntp_time (scalar_t__) ; 
 scalar_t__ ff_ntp_time () ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int update_size (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int mov_write_prft_tag(AVIOContext *pb, MOVMuxContext *mov, int tracks)
{
    int64_t pos = avio_tell(pb), pts_us, ntp_ts;
    MOVTrack *first_track;

    /* PRFT should be associated with at most one track. So, choosing only the
     * first track. */
    if (tracks > 0)
        return 0;
    first_track = &(mov->tracks[0]);

    if (!first_track->entry) {
        av_log(mov->fc, AV_LOG_WARNING, "Unable to write PRFT, no entries in the track\n");
        return 0;
    }

    if (first_track->cluster[0].pts == AV_NOPTS_VALUE) {
        av_log(mov->fc, AV_LOG_WARNING, "Unable to write PRFT, first PTS is invalid\n");
        return 0;
    }

    if (mov->write_prft == MOV_PRFT_SRC_WALLCLOCK) {
        ntp_ts = ff_get_formatted_ntp_time(ff_ntp_time());
    } else if (mov->write_prft == MOV_PRFT_SRC_PTS) {
        pts_us = av_rescale_q(first_track->cluster[0].pts,
                              first_track->st->time_base, AV_TIME_BASE_Q);
        ntp_ts = ff_get_formatted_ntp_time(pts_us + NTP_OFFSET_US);
    } else {
        av_log(mov->fc, AV_LOG_WARNING, "Unsupported PRFT box configuration: %d\n",
               mov->write_prft);
        return 0;
    }

    avio_wb32(pb, 0);                           // Size place holder
    ffio_wfourcc(pb, "prft");                   // Type
    avio_w8(pb, 1);                             // Version
    avio_wb24(pb, 0);                           // Flags
    avio_wb32(pb, first_track->track_id);       // reference track ID
    avio_wb64(pb, ntp_ts);                      // NTP time stamp
    avio_wb64(pb, first_track->cluster[0].pts); //media time
    return update_size(pb, pos);
}