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
typedef  int /*<<< orphan*/  MOVMuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int mov_write_mdta_hdlr_tag(AVIOContext *pb, MOVMuxContext *mov,
                                   AVFormatContext *s)
{
    avio_wb32(pb, 33); /* size */
    ffio_wfourcc(pb, "hdlr");
    avio_wb32(pb, 0);
    avio_wb32(pb, 0);
    ffio_wfourcc(pb, "mdta");
    avio_wb32(pb, 0);
    avio_wb32(pb, 0);
    avio_wb32(pb, 0);
    avio_w8(pb, 0);
    return 33;
}