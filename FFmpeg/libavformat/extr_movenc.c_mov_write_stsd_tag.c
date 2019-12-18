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
struct TYPE_11__ {TYPE_1__* par; } ;
struct TYPE_10__ {scalar_t__ codec_type; scalar_t__ codec_tag; } ;
typedef  TYPE_2__ MOVTrack ;
typedef  int /*<<< orphan*/  MOVMuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AVMEDIA_TYPE_SUBTITLE ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 scalar_t__ MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int mov_write_audio_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int mov_write_gpmd_tag (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int mov_write_rtp_tag (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int mov_write_subtitle_tag (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int mov_write_tmcd_tag (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int mov_write_video_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_stsd_tag(AVFormatContext *s, AVIOContext *pb, MOVMuxContext *mov, MOVTrack *track)
{
    int64_t pos = avio_tell(pb);
    int ret = 0;
    avio_wb32(pb, 0); /* size */
    ffio_wfourcc(pb, "stsd");
    avio_wb32(pb, 0); /* version & flags */
    avio_wb32(pb, 1); /* entry count */
    if (track->par->codec_type == AVMEDIA_TYPE_VIDEO)
        ret = mov_write_video_tag(s, pb, mov, track);
    else if (track->par->codec_type == AVMEDIA_TYPE_AUDIO)
        ret = mov_write_audio_tag(s, pb, mov, track);
    else if (track->par->codec_type == AVMEDIA_TYPE_SUBTITLE)
        ret = mov_write_subtitle_tag(pb, track);
    else if (track->par->codec_tag == MKTAG('r','t','p',' '))
        ret = mov_write_rtp_tag(pb, track);
    else if (track->par->codec_tag == MKTAG('t','m','c','d'))
        ret = mov_write_tmcd_tag(pb, track);
    else if (track->par->codec_tag == MKTAG('g','p','m','d'))
        ret = mov_write_gpmd_tag(pb, track);

    if (ret < 0)
        return ret;

    return update_size(pb, pos);
}