#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_12__ {int size; } ;
struct TYPE_11__ {int flags; } ;
struct TYPE_10__ {int entry; scalar_t__ mode; int track_id; int default_duration; int default_size; int default_sample_flags; TYPE_1__* par; TYPE_7__* cluster; } ;
struct TYPE_9__ {scalar_t__ codec_type; } ;
typedef  TYPE_2__ MOVTrack ;
typedef  TYPE_3__ MOVMuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int FF_MOV_FLAG_DEFAULT_BASE_MOOF ; 
 int FF_MOV_FLAG_OMIT_TFHD_OFFSET ; 
 scalar_t__ MODE_ISM ; 
 int MOV_FRAG_SAMPLE_FLAG_DEPENDS_NO ; 
 int MOV_FRAG_SAMPLE_FLAG_DEPENDS_YES ; 
 int MOV_FRAG_SAMPLE_FLAG_IS_NON_SYNC ; 
 int MOV_TFHD_BASE_DATA_OFFSET ; 
 int MOV_TFHD_DEFAULT_BASE_IS_MOOF ; 
 int MOV_TFHD_DEFAULT_DURATION ; 
 int MOV_TFHD_DEFAULT_FLAGS ; 
 int MOV_TFHD_DEFAULT_SIZE ; 
 int MOV_TFHD_DURATION_IS_EMPTY ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb24 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int get_cluster_duration (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int get_sample_flags (TYPE_2__*,TYPE_7__*) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_tfhd_tag(AVIOContext *pb, MOVMuxContext *mov,
                              MOVTrack *track, int64_t moof_offset)
{
    int64_t pos = avio_tell(pb);
    uint32_t flags = MOV_TFHD_DEFAULT_SIZE | MOV_TFHD_DEFAULT_DURATION |
                     MOV_TFHD_BASE_DATA_OFFSET;
    if (!track->entry) {
        flags |= MOV_TFHD_DURATION_IS_EMPTY;
    } else {
        flags |= MOV_TFHD_DEFAULT_FLAGS;
    }
    if (mov->flags & FF_MOV_FLAG_OMIT_TFHD_OFFSET)
        flags &= ~MOV_TFHD_BASE_DATA_OFFSET;
    if (mov->flags & FF_MOV_FLAG_DEFAULT_BASE_MOOF) {
        flags &= ~MOV_TFHD_BASE_DATA_OFFSET;
        flags |= MOV_TFHD_DEFAULT_BASE_IS_MOOF;
    }

    /* Don't set a default sample size, the silverlight player refuses
     * to play files with that set. Don't set a default sample duration,
     * WMP freaks out if it is set. Don't set a base data offset, PIFF
     * file format says it MUST NOT be set. */
    if (track->mode == MODE_ISM)
        flags &= ~(MOV_TFHD_DEFAULT_SIZE | MOV_TFHD_DEFAULT_DURATION |
                   MOV_TFHD_BASE_DATA_OFFSET);

    avio_wb32(pb, 0); /* size placeholder */
    ffio_wfourcc(pb, "tfhd");
    avio_w8(pb, 0); /* version */
    avio_wb24(pb, flags);

    avio_wb32(pb, track->track_id); /* track-id */
    if (flags & MOV_TFHD_BASE_DATA_OFFSET)
        avio_wb64(pb, moof_offset);
    if (flags & MOV_TFHD_DEFAULT_DURATION) {
        track->default_duration = get_cluster_duration(track, 0);
        avio_wb32(pb, track->default_duration);
    }
    if (flags & MOV_TFHD_DEFAULT_SIZE) {
        track->default_size = track->entry ? track->cluster[0].size : 1;
        avio_wb32(pb, track->default_size);
    } else
        track->default_size = -1;

    if (flags & MOV_TFHD_DEFAULT_FLAGS) {
        /* Set the default flags based on the second sample, if available.
         * If the first sample is different, that can be signaled via a separate field. */
        if (track->entry > 1)
            track->default_sample_flags = get_sample_flags(track, &track->cluster[1]);
        else
            track->default_sample_flags =
                track->par->codec_type == AVMEDIA_TYPE_VIDEO ?
                (MOV_FRAG_SAMPLE_FLAG_DEPENDS_YES | MOV_FRAG_SAMPLE_FLAG_IS_NON_SYNC) :
                MOV_FRAG_SAMPLE_FLAG_DEPENDS_NO;
        avio_wb32(pb, track->default_sample_flags);
    }

    return update_size(pb, pos);
}