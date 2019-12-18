#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_6__ {char* value; } ;
struct TYPE_5__ {int flags; int /*<<< orphan*/  metadata; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;
typedef  TYPE_2__ AVDictionaryEntry ;

/* Variables and functions */
 int AVFMT_FLAG_BITEXACT ; 
 char* LIBAVCODEC_IDENT ; 
 TYPE_2__* av_dict_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int language_code (char*) ; 
 int /*<<< orphan*/  mov_write_psp_udta_tag (int /*<<< orphan*/ *,char*,char*,int) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_uuidusmt_tag(AVIOContext *pb, AVFormatContext *s)
{
    AVDictionaryEntry *title = av_dict_get(s->metadata, "title", NULL, 0);
    int64_t pos, pos2;

    if (title) {
        pos = avio_tell(pb);
        avio_wb32(pb, 0); /* size placeholder*/
        ffio_wfourcc(pb, "uuid");
        ffio_wfourcc(pb, "USMT");
        avio_wb32(pb, 0x21d24fce); /* 96 bit UUID */
        avio_wb32(pb, 0xbb88695c);
        avio_wb32(pb, 0xfac9c740);

        pos2 = avio_tell(pb);
        avio_wb32(pb, 0); /* size placeholder*/
        ffio_wfourcc(pb, "MTDT");
        avio_wb16(pb, 4);

        // ?
        avio_wb16(pb, 0x0C);                 /* size */
        avio_wb32(pb, 0x0B);                 /* type */
        avio_wb16(pb, language_code("und")); /* language */
        avio_wb16(pb, 0x0);                  /* ? */
        avio_wb16(pb, 0x021C);               /* data */

        if (!(s->flags & AVFMT_FLAG_BITEXACT))
            mov_write_psp_udta_tag(pb, LIBAVCODEC_IDENT,      "eng", 0x04);
        mov_write_psp_udta_tag(pb, title->value,          "eng", 0x01);
        mov_write_psp_udta_tag(pb, "2006/04/01 11:11:11", "und", 0x03);

        update_size(pb, pos2);
        return update_size(pb, pos);
    }

    return 0;
}