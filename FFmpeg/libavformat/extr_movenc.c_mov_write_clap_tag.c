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
struct TYPE_5__ {int height; TYPE_1__* par; } ;
struct TYPE_4__ {int width; } ;
typedef  TYPE_2__ MOVTrack ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int mov_write_clap_tag(AVIOContext *pb, MOVTrack *track)
{
    avio_wb32(pb, 40);
    ffio_wfourcc(pb, "clap");
    avio_wb32(pb, track->par->width); /* apertureWidth_N */
    avio_wb32(pb, 1); /* apertureWidth_D (= 1) */
    avio_wb32(pb, track->height); /* apertureHeight_N */
    avio_wb32(pb, 1); /* apertureHeight_D (= 1) */
    avio_wb32(pb, 0); /* horizOff_N (= 0) */
    avio_wb32(pb, 1); /* horizOff_D (= 1) */
    avio_wb32(pb, 0); /* vertOff_N (= 0) */
    avio_wb32(pb, 1); /* vertOff_D (= 1) */
    return 40;
}