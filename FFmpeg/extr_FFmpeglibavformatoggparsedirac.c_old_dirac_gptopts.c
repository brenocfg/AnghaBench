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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_3__ {struct ogg* priv_data; } ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 

__attribute__((used)) static uint64_t old_dirac_gptopts(AVFormatContext *s, int idx, uint64_t gp,
                                  int64_t *dts)
{
    struct ogg *ogg = s->priv_data;
    struct ogg_stream *os = ogg->streams + idx;
    uint64_t iframe = gp >> 30;
    uint64_t pframe = gp & 0x3fffffff;

    if (!pframe)
        os->pflags |= AV_PKT_FLAG_KEY;

    return iframe + pframe;
}