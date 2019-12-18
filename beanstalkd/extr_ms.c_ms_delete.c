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
struct TYPE_4__ {size_t len; int /*<<< orphan*/  (* onremove ) (TYPE_1__*,void*,size_t) ;void** items; } ;
typedef  TYPE_1__ Ms ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,void*,size_t) ; 

__attribute__((used)) static int
ms_delete(Ms *a, size_t i)
{
    void *item;

    if (i >= a->len)
        return 0;
    item = a->items[i];
    a->items[i] = a->items[--a->len];

    /* it has already been removed now */
    if (a->onremove)
        a->onremove(a, item, i);
    return 1;
}