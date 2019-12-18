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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  ff; int /*<<< orphan*/  ss; int /*<<< orphan*/  mm; int /*<<< orphan*/  hh; int /*<<< orphan*/  drop; int /*<<< orphan*/  color; } ;
struct TYPE_5__ {TYPE_1__ tc; } ;
typedef  TYPE_2__ GXFContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  GXF_TIMECODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TRACK_AUX ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gxf_write_timecode_auxiliary(AVIOContext *pb, GXFContext *gxf)
{
    uint32_t timecode = GXF_TIMECODE(gxf->tc.color, gxf->tc.drop,
                                     gxf->tc.hh, gxf->tc.mm,
                                     gxf->tc.ss, gxf->tc.ff);

    avio_w8(pb, TRACK_AUX);
    avio_w8(pb, 8);
    avio_wl32(pb, timecode);
    /* reserved */
    avio_wl32(pb, 0);
    return 8;
}