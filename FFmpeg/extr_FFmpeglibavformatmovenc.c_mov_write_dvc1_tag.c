#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {int vos_len; int /*<<< orphan*/ * vos_data; } ;
typedef  TYPE_1__ MOVTrack ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int mov_write_dvc1_structs (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mov_write_dvc1_tag(AVIOContext *pb, MOVTrack *track)
{
    uint8_t buf[7] = { 0 };
    int ret;

    if ((ret = mov_write_dvc1_structs(track, buf)) < 0)
        return ret;

    avio_wb32(pb, track->vos_len + 8 + sizeof(buf));
    ffio_wfourcc(pb, "dvc1");
    avio_write(pb, buf, sizeof(buf));
    avio_write(pb, track->vos_data, track->vos_len);

    return 0;
}