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
struct TYPE_3__ {scalar_t__ mode; int /*<<< orphan*/  mdat_pos; } ;
typedef  TYPE_1__ MOVMuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 scalar_t__ MODE_MOV ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int mov_write_mdat_tag(AVIOContext *pb, MOVMuxContext *mov)
{
    avio_wb32(pb, 8);    // placeholder for extended size field (64 bit)
    ffio_wfourcc(pb, mov->mode == MODE_MOV ? "wide" : "free");

    mov->mdat_pos = avio_tell(pb);
    avio_wb32(pb, 0); /* size placeholder*/
    ffio_wfourcc(pb, "mdat");
    return 0;
}