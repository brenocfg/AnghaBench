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
struct TYPE_4__ {int len; int last; void** items; } ;
typedef  TYPE_1__ Ms ;

/* Variables and functions */
 int /*<<< orphan*/  ms_delete (TYPE_1__*,size_t) ; 

void *
ms_take(Ms *a)
{
    void *item;

    if (!a->len)
        return NULL;

    // The result of last behaviour is that ms_take returns the oldest elements
    // first, exception is a row of multiple take calls without inserts on ms
    // of even number of elements. See the test.
    a->last = a->last % a->len;
    item = a->items[a->last];
    ms_delete(a, a->last);
    ++a->last;
    return item;
}