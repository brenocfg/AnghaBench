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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_3__ {int /*<<< orphan*/  vos_len; int /*<<< orphan*/  vos_data; } ;
typedef  TYPE_1__ MOVTrack ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_isom_write_av1c (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_av1c_tag(AVIOContext *pb, MOVTrack *track)
{
    int64_t pos = avio_tell(pb);

    avio_wb32(pb, 0);
    ffio_wfourcc(pb, "av1C");
    ff_isom_write_av1c(pb, track->vos_data, track->vos_len);
    return update_size(pb, pos);
}