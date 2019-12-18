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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {int entry; TYPE_1__* cluster; } ;
struct TYPE_4__ {int flags; } ;
typedef  TYPE_2__ MOVTrack ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int MOV_DISPOSABLE_SAMPLE ; 
 int MOV_SAMPLE_DEPENDENCY_NO ; 
 int MOV_SAMPLE_DEPENDENCY_UNKNOWN ; 
 int MOV_SAMPLE_DEPENDENCY_YES ; 
 int MOV_SYNC_SAMPLE ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_sdtp_tag(AVIOContext *pb, MOVTrack *track)
{
    int i;
    uint8_t leading, dependent, reference, redundancy;
    int64_t pos = avio_tell(pb);
    avio_wb32(pb, 0); // size
    ffio_wfourcc(pb, "sdtp");
    avio_wb32(pb, 0); // version & flags
    for (i = 0; i < track->entry; i++) {
        dependent = MOV_SAMPLE_DEPENDENCY_YES;
        leading = reference = redundancy = MOV_SAMPLE_DEPENDENCY_UNKNOWN;
        if (track->cluster[i].flags & MOV_DISPOSABLE_SAMPLE) {
            reference = MOV_SAMPLE_DEPENDENCY_NO;
        }
        if (track->cluster[i].flags & MOV_SYNC_SAMPLE) {
            dependent = MOV_SAMPLE_DEPENDENCY_NO;
        }
        avio_w8(pb, (leading << 6)   | (dependent << 4) |
                    (reference << 2) | redundancy);
    }
    return update_size(pb, pos);
}