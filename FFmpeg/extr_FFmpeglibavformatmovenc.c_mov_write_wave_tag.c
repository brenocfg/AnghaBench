#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_11__ {TYPE_1__* par; int /*<<< orphan*/  tag; } ;
struct TYPE_10__ {scalar_t__ codec_id; } ;
typedef  TYPE_2__ MOVTrack ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_AAC ; 
 scalar_t__ AV_CODEC_ID_AC3 ; 
 scalar_t__ AV_CODEC_ID_ADPCM_IMA_WAV ; 
 scalar_t__ AV_CODEC_ID_ADPCM_MS ; 
 scalar_t__ AV_CODEC_ID_ALAC ; 
 scalar_t__ AV_CODEC_ID_AMR_NB ; 
 scalar_t__ AV_CODEC_ID_EAC3 ; 
 scalar_t__ AV_CODEC_ID_QDM2 ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ mov_pcm_be_gt16 (scalar_t__) ; 
 scalar_t__ mov_pcm_le_gt16 (scalar_t__) ; 
 int /*<<< orphan*/  mov_write_ac3_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  mov_write_amr_tag (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  mov_write_eac3_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  mov_write_enda_tag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mov_write_enda_tag_be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mov_write_esds_tag (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  mov_write_extradata_tag (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  mov_write_ms_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_wave_tag(AVFormatContext *s, AVIOContext *pb, MOVTrack *track)
{
    int64_t pos = avio_tell(pb);

    avio_wb32(pb, 0);     /* size */
    ffio_wfourcc(pb, "wave");

    if (track->par->codec_id != AV_CODEC_ID_QDM2) {
    avio_wb32(pb, 12);    /* size */
    ffio_wfourcc(pb, "frma");
    avio_wl32(pb, track->tag);
    }

    if (track->par->codec_id == AV_CODEC_ID_AAC) {
        /* useless atom needed by mplayer, ipod, not needed by quicktime */
        avio_wb32(pb, 12); /* size */
        ffio_wfourcc(pb, "mp4a");
        avio_wb32(pb, 0);
        mov_write_esds_tag(pb, track);
    } else if (mov_pcm_le_gt16(track->par->codec_id))  {
      mov_write_enda_tag(pb);
    } else if (mov_pcm_be_gt16(track->par->codec_id))  {
      mov_write_enda_tag_be(pb);
    } else if (track->par->codec_id == AV_CODEC_ID_AMR_NB) {
        mov_write_amr_tag(pb, track);
    } else if (track->par->codec_id == AV_CODEC_ID_AC3) {
        mov_write_ac3_tag(s, pb, track);
    } else if (track->par->codec_id == AV_CODEC_ID_EAC3) {
        mov_write_eac3_tag(s, pb, track);
    } else if (track->par->codec_id == AV_CODEC_ID_ALAC ||
               track->par->codec_id == AV_CODEC_ID_QDM2) {
        mov_write_extradata_tag(pb, track);
    } else if (track->par->codec_id == AV_CODEC_ID_ADPCM_MS ||
               track->par->codec_id == AV_CODEC_ID_ADPCM_IMA_WAV) {
        mov_write_ms_tag(s, pb, track);
    }

    avio_wb32(pb, 8);     /* size */
    avio_wb32(pb, 0);     /* null tag */

    return update_size(pb, pos);
}