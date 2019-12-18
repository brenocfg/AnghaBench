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
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int gxf_write_umf_media_timecode(AVIOContext *pb, int drop)
{
    avio_wl32(pb, drop); /* drop frame */
    avio_wl32(pb, 0); /* reserved */
    avio_wl32(pb, 0); /* reserved */
    avio_wl32(pb, 0); /* reserved */
    avio_wl32(pb, 0); /* reserved */
    avio_wl32(pb, 0); /* reserved */
    avio_wl32(pb, 0); /* reserved */
    avio_wl32(pb, 0); /* reserved */
    return 32;
}