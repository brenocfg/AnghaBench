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
struct TYPE_3__ {int count; int sum; } ;
typedef  TYPE_1__ RICEContext ;

/* Variables and functions */

__attribute__((used)) static int loco_get_rice_param(RICEContext *r)
{
    int cnt = 0;
    int val = r->count;

    while (r->sum > val && cnt < 9) {
        val <<= 1;
        cnt++;
    }

    return cnt;
}