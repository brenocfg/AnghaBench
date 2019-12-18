#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_3__ {int /*<<< orphan*/  tag; } ;
typedef  TYPE_1__ MOVTrack ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mov_cenc_write_schi_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ff_mov_cenc_write_sinf_tag(MOVTrack* track, AVIOContext *pb, uint8_t* kid)
{
    int64_t pos = avio_tell(pb);
    avio_wb32(pb, 0); /* size */
    ffio_wfourcc(pb, "sinf");

    /* frma */
    avio_wb32(pb, 12);    /* size */
    ffio_wfourcc(pb, "frma");
    avio_wl32(pb, track->tag);

    /* schm */
    avio_wb32(pb, 20);    /* size */
    ffio_wfourcc(pb, "schm");
    avio_wb32(pb, 0); /* version & flags */
    ffio_wfourcc(pb, "cenc");    /* scheme type*/
    avio_wb32(pb, 0x10000); /* scheme version */

    /* schi */
    mov_cenc_write_schi_tag(pb, kid);

    return update_size(pb, pos);
}