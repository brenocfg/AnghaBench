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
struct TYPE_3__ {int sum; int count; } ;
typedef  TYPE_1__ RICEContext ;

/* Variables and functions */

__attribute__((used)) static inline void loco_update_rice_param(RICEContext *r, int val)
{
    r->sum += val;
    r->count++;

    if (r->count == 16) {
        r->sum   >>= 1;
        r->count >>= 1;
    }
}