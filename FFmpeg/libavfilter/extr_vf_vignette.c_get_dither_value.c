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
struct TYPE_3__ {double dither; scalar_t__ do_dither; } ;
typedef  TYPE_1__ VignetteContext ;

/* Variables and functions */

__attribute__((used)) static inline double get_dither_value(VignetteContext *s)
{
    double dv = 0;
    if (s->do_dither) {
        dv = s->dither / (double)(1LL<<32);
        s->dither = s->dither * 1664525 + 1013904223;
    }
    return dv;
}