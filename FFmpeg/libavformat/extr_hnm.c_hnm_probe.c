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
struct TYPE_3__ {int buf_size; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 scalar_t__ AV_RL32 (int /*<<< orphan*/ *) ; 
 scalar_t__ HNM4_TAG ; 

__attribute__((used)) static int hnm_probe(const AVProbeData *p)
{
    if (p->buf_size < 4)
        return 0;

    // check for HNM4 header.
    // currently only HNM v4/v4A is supported
    if (AV_RL32(&p->buf[0]) == HNM4_TAG)
        return AVPROBE_SCORE_MAX;

    return 0;
}