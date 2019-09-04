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
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/ * counter; } ;
typedef  TYPE_1__ AudioBitScopeContext ;

/* Variables and functions */

__attribute__((used)) static void count_bits(AudioBitScopeContext *s, uint32_t sample, int max)
{
    int i;

    for (i = 0; i < max; i++) {
        if (sample & (1 << i))
            s->counter[i]++;
    }
}