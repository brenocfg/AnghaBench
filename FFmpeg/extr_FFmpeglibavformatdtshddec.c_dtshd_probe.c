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
 int AVPROBE_SCORE_MAX ; 
 scalar_t__ AV_RB64 (int /*<<< orphan*/ ) ; 
 scalar_t__ DTSHDHDR ; 

__attribute__((used)) static int dtshd_probe(const AVProbeData *p)
{
    if (AV_RB64(p->buf) == DTSHDHDR)
        return AVPROBE_SCORE_MAX;
    return 0;
}