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
struct TYPE_3__ {size_t len; void** items; } ;
typedef  TYPE_1__ Ms ;

/* Variables and functions */

int
ms_contains(Ms *a, void *item)
{
    size_t i;

    for (i = 0; i < a->len; i++) {
        if (a->items[i] == item)
            return 1;
    }
    return 0;
}