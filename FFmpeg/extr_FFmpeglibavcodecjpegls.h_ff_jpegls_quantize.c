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
struct TYPE_3__ {int T3; int T2; int T1; int near; } ;
typedef  TYPE_1__ JLSState ;

/* Variables and functions */

__attribute__((used)) static inline int ff_jpegls_quantize(JLSState *s, int v)
{
    if (v == 0)
        return 0;
    if (v < 0) {
        if (v <= -s->T3)
            return -4;
        if (v <= -s->T2)
            return -3;
        if (v <= -s->T1)
            return -2;
        if (v < -s->near)
            return -1;
        return 0;
    } else {
        if (v <= s->near)
            return 0;
        if (v < s->T1)
            return 1;
        if (v < s->T2)
            return 2;
        if (v < s->T3)
            return 3;
        return 4;
    }
}