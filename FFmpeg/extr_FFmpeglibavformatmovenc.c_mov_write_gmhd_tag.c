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
struct TYPE_6__ {scalar_t__ tag; TYPE_1__* par; } ;
struct TYPE_5__ {scalar_t__ codec_tag; } ;
typedef  TYPE_2__ MOVTrack ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 scalar_t__ MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mov_write_tcmi_tag (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_gmhd_tag(AVIOContext *pb, MOVTrack *track)
{
    int64_t pos = avio_tell(pb);
    avio_wb32(pb, 0);      /* size */
    ffio_wfourcc(pb, "gmhd");
    avio_wb32(pb, 0x18);   /* gmin size */
    ffio_wfourcc(pb, "gmin");/* generic media info */
    avio_wb32(pb, 0);      /* version & flags */
    avio_wb16(pb, 0x40);   /* graphics mode = */
    avio_wb16(pb, 0x8000); /* opColor (r?) */
    avio_wb16(pb, 0x8000); /* opColor (g?) */
    avio_wb16(pb, 0x8000); /* opColor (b?) */
    avio_wb16(pb, 0);      /* balance */
    avio_wb16(pb, 0);      /* reserved */

    /*
     * This special text atom is required for
     * Apple Quicktime chapters. The contents
     * don't appear to be documented, so the
     * bytes are copied verbatim.
     */
    if (track->tag != MKTAG('c','6','0','8')) {
    avio_wb32(pb, 0x2C);   /* size */
    ffio_wfourcc(pb, "text");
    avio_wb16(pb, 0x01);
    avio_wb32(pb, 0x00);
    avio_wb32(pb, 0x00);
    avio_wb32(pb, 0x00);
    avio_wb32(pb, 0x01);
    avio_wb32(pb, 0x00);
    avio_wb32(pb, 0x00);
    avio_wb32(pb, 0x00);
    avio_wb32(pb, 0x00004000);
    avio_wb16(pb, 0x0000);
    }

    if (track->par->codec_tag == MKTAG('t','m','c','d')) {
        int64_t tmcd_pos = avio_tell(pb);
        avio_wb32(pb, 0); /* size */
        ffio_wfourcc(pb, "tmcd");
        mov_write_tcmi_tag(pb, track);
        update_size(pb, tmcd_pos);
    } else if (track->par->codec_tag == MKTAG('g','p','m','d')) {
        int64_t gpmd_pos = avio_tell(pb);
        avio_wb32(pb, 0); /* size */
        ffio_wfourcc(pb, "gpmd");
        avio_wb32(pb, 0); /* version */
        update_size(pb, gpmd_pos);
    }
    return update_size(pb, pos);
}