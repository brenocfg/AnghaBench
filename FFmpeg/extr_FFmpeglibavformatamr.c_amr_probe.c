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
struct TYPE_3__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int /*<<< orphan*/  AMR_header ; 
 int AVPROBE_SCORE_MAX ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int amr_probe(const AVProbeData *p)
{
    // Only check for "#!AMR" which could be amr-wb, amr-nb.
    // This will also trigger multichannel files: "#!AMR_MC1.0\n" and
    // "#!AMR-WB_MC1.0\n" (not supported)

    if (!memcmp(p->buf, AMR_header, 5))
        return AVPROBE_SCORE_MAX;
    else
        return 0;
}