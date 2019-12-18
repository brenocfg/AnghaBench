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
typedef  int int64_t ;
struct TYPE_6__ {int flags; int nb_streams; TYPE_1__* tracks; } ;
struct TYPE_5__ {scalar_t__ nb_frag_info; } ;
typedef  TYPE_1__ MOVTrack ;
typedef  TYPE_2__ MOVMuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int FF_MOV_FLAG_ISML ; 
 int avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mov_write_tfra_tag (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int update_size (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mov_write_mfra_tag(AVIOContext *pb, MOVMuxContext *mov)
{
    int64_t pos = avio_tell(pb);
    int i;

    avio_wb32(pb, 0); /* size placeholder */
    ffio_wfourcc(pb, "mfra");
    /* An empty mfra atom is enough to indicate to the publishing point that
     * the stream has ended. */
    if (mov->flags & FF_MOV_FLAG_ISML)
        return update_size(pb, pos);

    for (i = 0; i < mov->nb_streams; i++) {
        MOVTrack *track = &mov->tracks[i];
        if (track->nb_frag_info)
            mov_write_tfra_tag(pb, track);
    }

    avio_wb32(pb, 16);
    ffio_wfourcc(pb, "mfro");
    avio_wb32(pb, 0); /* version + flags */
    avio_wb32(pb, avio_tell(pb) + 4 - pos);

    return update_size(pb, pos);
}