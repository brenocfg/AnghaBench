#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_14__ {scalar_t__ aes_ctr; } ;
struct TYPE_16__ {scalar_t__ has_keyframes; scalar_t__ entry; scalar_t__ mode; int flags; TYPE_1__* par; TYPE_13__ cenc; scalar_t__ has_disposable; } ;
struct TYPE_15__ {scalar_t__ codec_type; scalar_t__ codec_id; scalar_t__ codec_tag; } ;
typedef  TYPE_2__ MOVTrack ;
typedef  int /*<<< orphan*/  MOVMuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 scalar_t__ AV_CODEC_ID_AAC ; 
 scalar_t__ AV_CODEC_ID_OPUS ; 
 scalar_t__ AV_CODEC_ID_TRUEHD ; 
 scalar_t__ MKTAG (char,char,char,char) ; 
 scalar_t__ MODE_MOV ; 
 int /*<<< orphan*/  MOV_PARTIAL_SYNC_SAMPLE ; 
 int /*<<< orphan*/  MOV_SYNC_SAMPLE ; 
 int MOV_TRACK_CTTS ; 
 int MOV_TRACK_STPS ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_mov_cenc_write_stbl_atoms (TYPE_13__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mov_preroll_write_stbl_atoms (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int mov_write_ctts_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  mov_write_sdtp_tag (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  mov_write_stco_tag (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  mov_write_stsc_tag (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int mov_write_stsd_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  mov_write_stss_tag (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mov_write_stsz_tag (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  mov_write_stts_tag (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_stbl_tag(AVFormatContext *s, AVIOContext *pb, MOVMuxContext *mov, MOVTrack *track)
{
    int64_t pos = avio_tell(pb);
    int ret = 0;

    avio_wb32(pb, 0); /* size */
    ffio_wfourcc(pb, "stbl");
    if ((ret = mov_write_stsd_tag(s, pb, mov, track)) < 0)
        return ret;
    mov_write_stts_tag(pb, track);
    if ((track->par->codec_type == AVMEDIA_TYPE_VIDEO ||
         track->par->codec_id == AV_CODEC_ID_TRUEHD ||
         track->par->codec_tag == MKTAG('r','t','p',' ')) &&
        track->has_keyframes && track->has_keyframes < track->entry)
        mov_write_stss_tag(pb, track, MOV_SYNC_SAMPLE);
    if (track->par->codec_type == AVMEDIA_TYPE_VIDEO && track->has_disposable)
        mov_write_sdtp_tag(pb, track);
    if (track->mode == MODE_MOV && track->flags & MOV_TRACK_STPS)
        mov_write_stss_tag(pb, track, MOV_PARTIAL_SYNC_SAMPLE);
    if (track->par->codec_type == AVMEDIA_TYPE_VIDEO &&
        track->flags & MOV_TRACK_CTTS && track->entry) {

        if ((ret = mov_write_ctts_tag(s, pb, track)) < 0)
            return ret;
    }
    mov_write_stsc_tag(pb, track);
    mov_write_stsz_tag(pb, track);
    mov_write_stco_tag(pb, track);
    if (track->cenc.aes_ctr) {
        ff_mov_cenc_write_stbl_atoms(&track->cenc, pb);
    }
    if (track->par->codec_id == AV_CODEC_ID_OPUS || track->par->codec_id == AV_CODEC_ID_AAC) {
        mov_preroll_write_stbl_atoms(pb, track);
    }
    return update_size(pb, pos);
}