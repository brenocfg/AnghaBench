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
typedef  int /*<<< orphan*/  uuid ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {TYPE_1__* cluster; scalar_t__ end_pts; scalar_t__ frag_start; scalar_t__ start_dts; } ;
struct TYPE_4__ {scalar_t__ cts; scalar_t__ dts; } ;
typedef  TYPE_2__ MOVTrack ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb24 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb64 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int const*,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_tfxd_tag(AVIOContext *pb, MOVTrack *track)
{
    int64_t pos = avio_tell(pb);
    static const uint8_t uuid[] = {
        0x6d, 0x1d, 0x9b, 0x05, 0x42, 0xd5, 0x44, 0xe6,
        0x80, 0xe2, 0x14, 0x1d, 0xaf, 0xf7, 0x57, 0xb2
    };

    avio_wb32(pb, 0); /* size placeholder */
    ffio_wfourcc(pb, "uuid");
    avio_write(pb, uuid, sizeof(uuid));
    avio_w8(pb, 1);
    avio_wb24(pb, 0);
    avio_wb64(pb, track->start_dts + track->frag_start +
                  track->cluster[0].cts);
    avio_wb64(pb, track->end_pts -
                  (track->cluster[0].dts + track->cluster[0].cts));

    return update_size(pb, pos);
}