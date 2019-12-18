#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ pos; scalar_t__ pts; } ;
typedef  TYPE_1__ AVPacket ;

/* Variables and functions */

__attribute__((used)) static int cmp_pkt_sub_pos_ts(const void *a, const void *b)
{
    const AVPacket *s1 = a;
    const AVPacket *s2 = b;
    if (s1->pos == s2->pos) {
        if (s1->pts == s2->pts)
            return 0;
        return s1->pts > s2->pts ? 1 : -1;
    }
    return s1->pos > s2->pos ? 1 : -1;
}