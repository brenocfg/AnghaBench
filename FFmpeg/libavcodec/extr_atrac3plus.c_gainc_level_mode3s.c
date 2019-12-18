#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int num_points; int* lev_code; } ;
typedef  TYPE_1__ AtracGainInfo ;

/* Variables and functions */

__attribute__((used)) static inline void gainc_level_mode3s(AtracGainInfo *dst, AtracGainInfo *ref)
{
    int i;

    for (i = 0; i < dst->num_points; i++)
        dst->lev_code[i] = (i >= ref->num_points) ? 7 : ref->lev_code[i];
}