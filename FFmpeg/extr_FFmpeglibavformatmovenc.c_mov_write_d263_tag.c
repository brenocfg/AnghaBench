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
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int mov_write_d263_tag(AVIOContext *pb)
{
    avio_wb32(pb, 0xf); /* size */
    ffio_wfourcc(pb, "d263");
    ffio_wfourcc(pb, "FFMP");
    avio_w8(pb, 0); /* decoder version */
    /* FIXME use AVCodecContext level/profile, when encoder will set values */
    avio_w8(pb, 0xa); /* level */
    avio_w8(pb, 0); /* profile */
    return 0xf;
}