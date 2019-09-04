#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_8__ {scalar_t__ tag; scalar_t__ mode; TYPE_1__* par; } ;
struct TYPE_7__ {scalar_t__ codec_type; } ;
typedef  TYPE_2__ MOVTrack ;
typedef  int /*<<< orphan*/  MOVMuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AVMEDIA_TYPE_SUBTITLE ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 scalar_t__ MKTAG (char,char,char,char) ; 
 scalar_t__ MODE_MOV ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ is_clcp_track (TYPE_2__*) ; 
 int /*<<< orphan*/  mov_write_dinf_tag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mov_write_gmhd_tag (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  mov_write_hdlr_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mov_write_hmhd_tag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mov_write_nmhd_tag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mov_write_smhd_tag (int /*<<< orphan*/ *) ; 
 int mov_write_stbl_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  mov_write_vmhd_tag (int /*<<< orphan*/ *) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_minf_tag(AVFormatContext *s, AVIOContext *pb, MOVMuxContext *mov, MOVTrack *track)
{
    int64_t pos = avio_tell(pb);
    int ret;

    avio_wb32(pb, 0); /* size */
    ffio_wfourcc(pb, "minf");
    if (track->par->codec_type == AVMEDIA_TYPE_VIDEO)
        mov_write_vmhd_tag(pb);
    else if (track->par->codec_type == AVMEDIA_TYPE_AUDIO)
        mov_write_smhd_tag(pb);
    else if (track->par->codec_type == AVMEDIA_TYPE_SUBTITLE) {
        if (track->tag == MKTAG('t','e','x','t') || is_clcp_track(track)) {
            mov_write_gmhd_tag(pb, track);
        } else {
            mov_write_nmhd_tag(pb);
        }
    } else if (track->tag == MKTAG('r','t','p',' ')) {
        mov_write_hmhd_tag(pb);
    } else if (track->tag == MKTAG('t','m','c','d')) {
        if (track->mode != MODE_MOV)
            mov_write_nmhd_tag(pb);
        else
            mov_write_gmhd_tag(pb, track);
    } else if (track->tag == MKTAG('g','p','m','d')) {
        mov_write_gmhd_tag(pb, track);
    }
    if (track->mode == MODE_MOV) /* ISO 14496-12 8.4.3.1 specifies hdlr only within mdia or meta boxes */
        mov_write_hdlr_tag(s, pb, NULL);
    mov_write_dinf_tag(pb);
    if ((ret = mov_write_stbl_tag(s, pb, mov, track)) < 0)
        return ret;
    return update_size(pb, pos);
}