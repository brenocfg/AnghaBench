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
struct TYPE_3__ {scalar_t__ mode; } ;
typedef  TYPE_1__ MOVTrack ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 scalar_t__ MODE_MOV ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int mov_write_amr_tag(AVIOContext *pb, MOVTrack *track)
{
    avio_wb32(pb, 0x11); /* size */
    if (track->mode == MODE_MOV) ffio_wfourcc(pb, "samr");
    else                         ffio_wfourcc(pb, "damr");
    ffio_wfourcc(pb, "FFMP");
    avio_w8(pb, 0); /* decoder version */

    avio_wb16(pb, 0x81FF); /* Mode set (all modes for AMR_NB) */
    avio_w8(pb, 0x00); /* Mode change period (no restriction) */
    avio_w8(pb, 0x01); /* Frames per sample */
    return 0x11;
}