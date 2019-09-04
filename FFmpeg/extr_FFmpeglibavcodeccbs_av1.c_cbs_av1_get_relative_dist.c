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
struct TYPE_3__ {int order_hint_bits_minus_1; int /*<<< orphan*/  enable_order_hint; } ;
typedef  TYPE_1__ AV1RawSequenceHeader ;

/* Variables and functions */

__attribute__((used)) static int cbs_av1_get_relative_dist(const AV1RawSequenceHeader *seq,
                                     unsigned int a, unsigned int b)
{
    unsigned int diff, m;
    if (!seq->enable_order_hint)
        return 0;
    diff = a - b;
    m = 1 << seq->order_hint_bits_minus_1;
    diff = (diff & (m - 1)) - (diff & m);
    return diff;
}