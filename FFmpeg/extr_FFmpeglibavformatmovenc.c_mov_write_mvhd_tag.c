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
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {int nb_streams; int flags; scalar_t__ time; TYPE_1__* tracks; } ;
struct TYPE_4__ {scalar_t__ entry; int track_id; scalar_t__ timescale; int /*<<< orphan*/  track_duration; } ;
typedef  TYPE_2__ MOVMuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_ROUND_UP ; 
 int FF_MOV_FLAG_EMPTY_MOOV ; 
 int MOV_TIMESCALE ; 
 scalar_t__ UINT32_MAX ; 
 scalar_t__ av_rescale_rnd (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb24 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb64 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  write_matrix (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_mvhd_tag(AVIOContext *pb, MOVMuxContext *mov)
{
    int max_track_id = 1, i;
    int64_t max_track_len = 0;
    int version;

    for (i = 0; i < mov->nb_streams; i++) {
        if (mov->tracks[i].entry > 0 && mov->tracks[i].timescale) {
            int64_t max_track_len_temp = av_rescale_rnd(mov->tracks[i].track_duration,
                                                MOV_TIMESCALE,
                                                mov->tracks[i].timescale,
                                                AV_ROUND_UP);
            if (max_track_len < max_track_len_temp)
                max_track_len = max_track_len_temp;
            if (max_track_id < mov->tracks[i].track_id)
                max_track_id = mov->tracks[i].track_id;
        }
    }
    /* If using delay_moov, make sure the output is the same as if no
     * samples had been written yet. */
    if (mov->flags & FF_MOV_FLAG_EMPTY_MOOV) {
        max_track_len = 0;
        max_track_id  = 1;
    }

    version = max_track_len < UINT32_MAX ? 0 : 1;
    avio_wb32(pb, version == 1 ? 120 : 108); /* size */

    ffio_wfourcc(pb, "mvhd");
    avio_w8(pb, version);
    avio_wb24(pb, 0); /* flags */
    if (version == 1) {
        avio_wb64(pb, mov->time);
        avio_wb64(pb, mov->time);
    } else {
        avio_wb32(pb, mov->time); /* creation time */
        avio_wb32(pb, mov->time); /* modification time */
    }
    avio_wb32(pb, MOV_TIMESCALE);
    (version == 1) ? avio_wb64(pb, max_track_len) : avio_wb32(pb, max_track_len); /* duration of longest track */

    avio_wb32(pb, 0x00010000); /* reserved (preferred rate) 1.0 = normal */
    avio_wb16(pb, 0x0100); /* reserved (preferred volume) 1.0 = normal */
    avio_wb16(pb, 0); /* reserved */
    avio_wb32(pb, 0); /* reserved */
    avio_wb32(pb, 0); /* reserved */

    /* Matrix structure */
    write_matrix(pb, 1, 0, 0, 1, 0, 0);

    avio_wb32(pb, 0); /* reserved (preview time) */
    avio_wb32(pb, 0); /* reserved (preview duration) */
    avio_wb32(pb, 0); /* reserved (poster time) */
    avio_wb32(pb, 0); /* reserved (selection time) */
    avio_wb32(pb, 0); /* reserved (selection duration) */
    avio_wb32(pb, 0); /* reserved (current time) */
    avio_wb32(pb, max_track_id + 1); /* Next track id */
    return 0x6c;
}