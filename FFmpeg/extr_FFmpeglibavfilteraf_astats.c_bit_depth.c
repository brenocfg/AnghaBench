#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_6__ {unsigned int den; scalar_t__ num; } ;
struct TYPE_5__ {unsigned int maxbitdepth; } ;
typedef  TYPE_1__ AudioStatsContext ;
typedef  TYPE_2__ AVRational ;

/* Variables and functions */

__attribute__((used)) static void bit_depth(AudioStatsContext *s, uint64_t mask, uint64_t imask, AVRational *depth)
{
    unsigned result = s->maxbitdepth;

    mask = mask & (~imask);

    for (; result && !(mask & 1); --result, mask >>= 1);

    depth->den = result;
    depth->num = 0;

    for (; result; --result, mask >>= 1)
        if (mask & 1)
            depth->num++;
}