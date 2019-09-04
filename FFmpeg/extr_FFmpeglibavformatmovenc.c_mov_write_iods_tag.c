#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_7__ {int iods_audio_profile; int iods_video_profile; int nb_streams; int flags; TYPE_2__* tracks; } ;
struct TYPE_6__ {scalar_t__ entry; TYPE_1__* par; } ;
struct TYPE_5__ {scalar_t__ codec_type; } ;
typedef  TYPE_3__ MOVMuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int FF_MOV_FLAG_EMPTY_MOOV ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  put_descr (int /*<<< orphan*/ *,int,int) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_iods_tag(AVIOContext *pb, MOVMuxContext *mov)
{
    int i, has_audio = 0, has_video = 0;
    int64_t pos = avio_tell(pb);
    int audio_profile = mov->iods_audio_profile;
    int video_profile = mov->iods_video_profile;
    for (i = 0; i < mov->nb_streams; i++) {
        if (mov->tracks[i].entry > 0 || mov->flags & FF_MOV_FLAG_EMPTY_MOOV) {
            has_audio |= mov->tracks[i].par->codec_type == AVMEDIA_TYPE_AUDIO;
            has_video |= mov->tracks[i].par->codec_type == AVMEDIA_TYPE_VIDEO;
        }
    }
    if (audio_profile < 0)
        audio_profile = 0xFF - has_audio;
    if (video_profile < 0)
        video_profile = 0xFF - has_video;
    avio_wb32(pb, 0x0); /* size */
    ffio_wfourcc(pb, "iods");
    avio_wb32(pb, 0);    /* version & flags */
    put_descr(pb, 0x10, 7);
    avio_wb16(pb, 0x004f);
    avio_w8(pb, 0xff);
    avio_w8(pb, 0xff);
    avio_w8(pb, audio_profile);
    avio_w8(pb, video_profile);
    avio_w8(pb, 0xff);
    return update_size(pb, pos);
}