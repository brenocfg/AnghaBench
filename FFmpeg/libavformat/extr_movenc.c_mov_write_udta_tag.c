#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_13__ {scalar_t__ nb_chapters; } ;
struct TYPE_12__ {int mode; int flags; } ;
typedef  TYPE_1__ MOVMuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int FF_MOV_FLAG_DISABLE_CHPL ; 
 int FF_MOV_FLAG_USE_MDTA ; 
 int MODE_3GP ; 
 int MODE_MOV ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int avio_close_dyn_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int avio_open_dyn_buf (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mov_write_3gp_udta_tag (int /*<<< orphan*/ *,TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  mov_write_chpl_tag (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  mov_write_loci_tag (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mov_write_meta_tag (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  mov_write_raw_metadata_tag (TYPE_2__*,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  mov_write_string_metadata (TYPE_2__*,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_udta_tag(AVIOContext *pb, MOVMuxContext *mov,
                              AVFormatContext *s)
{
    AVIOContext *pb_buf;
    int ret, size;
    uint8_t *buf;

    ret = avio_open_dyn_buf(&pb_buf);
    if (ret < 0)
        return ret;

    if (mov->mode & MODE_3GP) {
        mov_write_3gp_udta_tag(pb_buf, s, "perf", "artist");
        mov_write_3gp_udta_tag(pb_buf, s, "titl", "title");
        mov_write_3gp_udta_tag(pb_buf, s, "auth", "author");
        mov_write_3gp_udta_tag(pb_buf, s, "gnre", "genre");
        mov_write_3gp_udta_tag(pb_buf, s, "dscp", "comment");
        mov_write_3gp_udta_tag(pb_buf, s, "albm", "album");
        mov_write_3gp_udta_tag(pb_buf, s, "cprt", "copyright");
        mov_write_3gp_udta_tag(pb_buf, s, "yrrc", "date");
        mov_write_loci_tag(s, pb_buf);
    } else if (mov->mode == MODE_MOV && !(mov->flags & FF_MOV_FLAG_USE_MDTA)) { // the title field breaks gtkpod with mp4 and my suspicion is that stuff is not valid in mp4
        mov_write_string_metadata(s, pb_buf, "\251ART", "artist",      0);
        mov_write_string_metadata(s, pb_buf, "\251nam", "title",       0);
        mov_write_string_metadata(s, pb_buf, "\251aut", "author",      0);
        mov_write_string_metadata(s, pb_buf, "\251alb", "album",       0);
        mov_write_string_metadata(s, pb_buf, "\251day", "date",        0);
        mov_write_string_metadata(s, pb_buf, "\251swr", "encoder",     0);
        // currently ignored by mov.c
        mov_write_string_metadata(s, pb_buf, "\251des", "comment",     0);
        // add support for libquicktime, this atom is also actually read by mov.c
        mov_write_string_metadata(s, pb_buf, "\251cmt", "comment",     0);
        mov_write_string_metadata(s, pb_buf, "\251gen", "genre",       0);
        mov_write_string_metadata(s, pb_buf, "\251cpy", "copyright",   0);
        mov_write_string_metadata(s, pb_buf, "\251mak", "make",        0);
        mov_write_string_metadata(s, pb_buf, "\251mod", "model",       0);
        mov_write_string_metadata(s, pb_buf, "\251xyz", "location",    0);
        mov_write_string_metadata(s, pb_buf, "\251key", "keywords",    0);
        mov_write_raw_metadata_tag(s, pb_buf, "XMP_", "xmp");
    } else {
        /* iTunes meta data */
        mov_write_meta_tag(pb_buf, mov, s);
        mov_write_loci_tag(s, pb_buf);
    }

    if (s->nb_chapters && !(mov->flags & FF_MOV_FLAG_DISABLE_CHPL))
        mov_write_chpl_tag(pb_buf, s);

    if ((size = avio_close_dyn_buf(pb_buf, &buf)) > 0) {
        avio_wb32(pb, size + 8);
        ffio_wfourcc(pb, "udta");
        avio_write(pb, buf, size);
    }
    av_free(buf);

    return 0;
}