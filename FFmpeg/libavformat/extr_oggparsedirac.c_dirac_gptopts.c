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
struct ogg_stream {int /*<<< orphan*/  pflags; } ;
struct ogg {struct ogg_stream* streams; } ;
typedef  int int64_t ;
struct TYPE_3__ {struct ogg* priv_data; } ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 

__attribute__((used)) static uint64_t dirac_gptopts(AVFormatContext *s, int idx, uint64_t granule,
                              int64_t *dts_out)
{
    int64_t gp = granule;
    struct ogg *ogg = s->priv_data;
    struct ogg_stream *os = ogg->streams + idx;

    unsigned dist  = ((gp >> 14) & 0xff00) | (gp & 0xff);
    int64_t  dts   = (gp >> 31);
    int64_t  pts   = dts + ((gp >> 9) & 0x1fff);

    if (!dist)
        os->pflags |= AV_PKT_FLAG_KEY;

    if (dts_out)
        *dts_out = dts;

    return pts;
}