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
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int mov_write_hmhd_tag(AVIOContext *pb)
{
    /* This atom must be present, but leaving the values at zero
     * seems harmless. */
    avio_wb32(pb, 28); /* size */
    ffio_wfourcc(pb, "hmhd");
    avio_wb32(pb, 0); /* version, flags */
    avio_wb16(pb, 0); /* maxPDUsize */
    avio_wb16(pb, 0); /* avgPDUsize */
    avio_wb32(pb, 0); /* maxbitrate */
    avio_wb32(pb, 0); /* avgbitrate */
    avio_wb32(pb, 0); /* reserved */
    return 28;
}