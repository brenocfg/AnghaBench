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
typedef  int /*<<< orphan*/  GXFStreamContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_double2int (int) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wl64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gxf_write_umf_media_audio(AVIOContext *pb, GXFStreamContext *sc)
{
    avio_wl64(pb, av_double2int(1)); /* sound level to begin to */
    avio_wl64(pb, av_double2int(1)); /* sound level to begin to */
    avio_wl32(pb, 0); /* number of fields over which to ramp up sound level */
    avio_wl32(pb, 0); /* number of fields over which to ramp down sound level */
    avio_wl32(pb, 0); /* reserved */
    avio_wl32(pb, 0); /* reserved */
    return 32;
}