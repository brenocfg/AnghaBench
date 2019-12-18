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
struct TYPE_3__ {int items_count; void** items; } ;
typedef  TYPE_1__ hb_list_t ;

/* Variables and functions */

void * hb_list_item( const hb_list_t * l, int i )
{
    if( l == NULL || i < 0 || i >= l->items_count )
    {
        return NULL;
    }

    return l->items[i];
}