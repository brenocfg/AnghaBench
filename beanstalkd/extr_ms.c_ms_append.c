#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ len; scalar_t__ cap; int /*<<< orphan*/  (* oninsert ) (TYPE_1__*,void*,scalar_t__) ;void** items; } ;
typedef  TYPE_1__ Ms ;

/* Variables and functions */
 int /*<<< orphan*/  grow (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,void*,scalar_t__) ; 

int
ms_append(Ms *a, void *item)
{
    if (a->len >= a->cap && !grow(a))
        return 0;

    a->items[a->len++] = item;
    if (a->oninsert)
        a->oninsert(a, item, a->len - 1);
    return 1;
}