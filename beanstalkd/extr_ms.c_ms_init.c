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
typedef  void* ms_event_fn ;
struct TYPE_3__ {void* onremove; void* oninsert; int /*<<< orphan*/ * items; scalar_t__ last; scalar_t__ cap; scalar_t__ len; } ;
typedef  TYPE_1__ Ms ;

/* Variables and functions */

void
ms_init(Ms *a, ms_event_fn oninsert, ms_event_fn onremove)
{
    a->len = a->cap = a->last = 0;
    a->items = NULL;
    a->oninsert = oninsert;
    a->onremove = onremove;
}