#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_10__ {int nb_streams; TYPE_3__** streams; TYPE_2__* priv_data; } ;
struct TYPE_9__ {TYPE_1__* codecpar; } ;
struct TYPE_8__ {char* major_brand; int mode; int flags; } ;
struct TYPE_7__ {scalar_t__ codec_type; scalar_t__ codec_id; } ;
typedef  TYPE_2__ MOVMuxContext ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 scalar_t__ AV_CODEC_ID_H264 ; 
 int FF_MOV_FLAG_DASH ; 
 int FF_MOV_FLAG_DEFAULT_BASE_MOOF ; 
 int FF_MOV_FLAG_FRAGMENT ; 
 int FF_MOV_FLAG_GLOBAL_SIDX ; 
 int FF_MOV_FLAG_NEGATIVE_CTS_OFFSETS ; 
 int MODE_3G2 ; 
 int MODE_3GP ; 
 int MODE_F4V ; 
 int MODE_IPOD ; 
 int MODE_ISM ; 
 int MODE_MOV ; 
 int MODE_MP4 ; 
 int MODE_PSP ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ is_cover_image (TYPE_3__*) ; 
 int strlen (char*) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_ftyp_tag(AVIOContext *pb, AVFormatContext *s)
{
    MOVMuxContext *mov = s->priv_data;
    int64_t pos = avio_tell(pb);
    int has_h264 = 0, has_video = 0;
    int minor = 0x200;
    int i;

    for (i = 0; i < s->nb_streams; i++) {
        AVStream *st = s->streams[i];
        if (is_cover_image(st))
            continue;
        if (st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
            has_video = 1;
        if (st->codecpar->codec_id == AV_CODEC_ID_H264)
            has_h264 = 1;
    }

    avio_wb32(pb, 0); /* size */
    ffio_wfourcc(pb, "ftyp");

    if (mov->major_brand && strlen(mov->major_brand) >= 4)
        ffio_wfourcc(pb, mov->major_brand);
    else if (mov->mode == MODE_3GP) {
        ffio_wfourcc(pb, has_h264 ? "3gp6"  : "3gp4");
        minor =     has_h264 ?   0x100 :   0x200;
    } else if (mov->mode & MODE_3G2) {
        ffio_wfourcc(pb, has_h264 ? "3g2b"  : "3g2a");
        minor =     has_h264 ? 0x20000 : 0x10000;
    } else if (mov->mode == MODE_PSP)
        ffio_wfourcc(pb, "MSNV");
    else if (mov->mode == MODE_MP4 && mov->flags & FF_MOV_FLAG_DEFAULT_BASE_MOOF)
        ffio_wfourcc(pb, "iso5"); // Required when using default-base-is-moof
    else if (mov->mode == MODE_MP4 && mov->flags & FF_MOV_FLAG_NEGATIVE_CTS_OFFSETS)
        ffio_wfourcc(pb, "iso4");
    else if (mov->mode == MODE_MP4)
        ffio_wfourcc(pb, "isom");
    else if (mov->mode == MODE_IPOD)
        ffio_wfourcc(pb, has_video ? "M4V ":"M4A ");
    else if (mov->mode == MODE_ISM)
        ffio_wfourcc(pb, "isml");
    else if (mov->mode == MODE_F4V)
        ffio_wfourcc(pb, "f4v ");
    else
        ffio_wfourcc(pb, "qt  ");

    avio_wb32(pb, minor);

    if (mov->mode == MODE_MOV)
        ffio_wfourcc(pb, "qt  ");
    else if (mov->mode == MODE_ISM) {
        ffio_wfourcc(pb, "piff");
    } else if (!(mov->flags & FF_MOV_FLAG_DEFAULT_BASE_MOOF)) {
        ffio_wfourcc(pb, "isom");
        ffio_wfourcc(pb, "iso2");
        if (has_h264)
            ffio_wfourcc(pb, "avc1");
    }

    // We add tfdt atoms when fragmenting, signal this with the iso6 compatible
    // brand. This is compatible with users that don't understand tfdt.
    if (mov->flags & FF_MOV_FLAG_FRAGMENT && mov->mode != MODE_ISM)
        ffio_wfourcc(pb, "iso6");

    if (mov->mode == MODE_3GP)
        ffio_wfourcc(pb, has_h264 ? "3gp6":"3gp4");
    else if (mov->mode & MODE_3G2)
        ffio_wfourcc(pb, has_h264 ? "3g2b":"3g2a");
    else if (mov->mode == MODE_PSP)
        ffio_wfourcc(pb, "MSNV");
    else if (mov->mode == MODE_MP4)
        ffio_wfourcc(pb, "mp41");

    if (mov->flags & FF_MOV_FLAG_DASH && mov->flags & FF_MOV_FLAG_GLOBAL_SIDX)
        ffio_wfourcc(pb, "dash");

    return update_size(pb, pos);
}