#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int mov_write_uuid_tag_ipod(AVIOContext *pb)
{
    avio_wb32(pb, 28);
    ffio_wfourcc(pb, "uuid");
    avio_wb32(pb, 0x6b6840f2);
    avio_wb32(pb, 0x5f244fc5);
    avio_wb32(pb, 0xba39a51b);
    avio_wb32(pb, 0xcf0323f3);
    avio_wb32(pb, 0x0);
    return 28;
}