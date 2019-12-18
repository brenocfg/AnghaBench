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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {int entry; TYPE_1__* cluster; } ;
struct TYPE_4__ {int flags; } ;
typedef  TYPE_2__ MOVTrack ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int MOV_SYNC_SAMPLE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_stss_tag(AVIOContext *pb, MOVTrack *track, uint32_t flag)
{
    int64_t curpos, entryPos;
    int i, index = 0;
    int64_t pos = avio_tell(pb);
    avio_wb32(pb, 0); // size
    ffio_wfourcc(pb, flag == MOV_SYNC_SAMPLE ? "stss" : "stps");
    avio_wb32(pb, 0); // version & flags
    entryPos = avio_tell(pb);
    avio_wb32(pb, track->entry); // entry count
    for (i = 0; i < track->entry; i++) {
        if (track->cluster[i].flags & flag) {
            avio_wb32(pb, i + 1);
            index++;
        }
    }
    curpos = avio_tell(pb);
    avio_seek(pb, entryPos, SEEK_SET);
    avio_wb32(pb, index); // rewrite size
    avio_seek(pb, curpos, SEEK_SET);
    return update_size(pb, pos);
}