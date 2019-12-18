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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct ogg_stream {int /*<<< orphan*/  pflags; } ;
struct ogg {struct ogg_stream* streams; } ;
typedef  int int64_t ;
struct TYPE_3__ {struct ogg* priv_data; } ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 

__attribute__((used)) static uint64_t vp8_gptopts(AVFormatContext *s, int idx,
                            uint64_t granule, int64_t *dts)
{
    struct ogg *ogg = s->priv_data;
    struct ogg_stream *os = ogg->streams + idx;

    int invcnt    = !((granule >> 30) & 3);
    // If page granule is that of an invisible vp8 frame, its pts will be
    // that of the end of the next visible frame. We subtract 1 for those
    // to prevent messing up pts calculations.
    uint64_t pts  = (granule >> 32) - invcnt;
    uint32_t dist = (granule >>  3) & 0x07ffffff;

    if (!dist)
        os->pflags |= AV_PKT_FLAG_KEY;

    if (dts)
        *dts = pts;

    return pts;
}