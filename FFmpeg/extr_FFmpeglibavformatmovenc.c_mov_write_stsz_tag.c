#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {int entry; TYPE_1__* cluster; } ;
struct TYPE_4__ {int size; int entries; } ;
typedef  TYPE_2__ MOVTrack ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int FFMAX (int,int) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_stsz_tag(AVIOContext *pb, MOVTrack *track)
{
    int equalChunks = 1;
    int i, j, entries = 0, tst = -1, oldtst = -1;

    int64_t pos = avio_tell(pb);
    avio_wb32(pb, 0); /* size */
    ffio_wfourcc(pb, "stsz");
    avio_wb32(pb, 0); /* version & flags */

    for (i = 0; i < track->entry; i++) {
        tst = track->cluster[i].size / track->cluster[i].entries;
        if (oldtst != -1 && tst != oldtst)
            equalChunks = 0;
        oldtst = tst;
        entries += track->cluster[i].entries;
    }
    if (equalChunks && track->entry) {
        int sSize = track->entry ? track->cluster[0].size / track->cluster[0].entries : 0;
        sSize = FFMAX(1, sSize); // adpcm mono case could make sSize == 0
        avio_wb32(pb, sSize); // sample size
        avio_wb32(pb, entries); // sample count
    } else {
        avio_wb32(pb, 0); // sample size
        avio_wb32(pb, entries); // sample count
        for (i = 0; i < track->entry; i++) {
            for (j = 0; j < track->cluster[i].entries; j++) {
                avio_wb32(pb, track->cluster[i].size /
                          track->cluster[i].entries);
            }
        }
    }
    return update_size(pb, pos);
}