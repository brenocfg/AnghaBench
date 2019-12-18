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
 int /*<<< orphan*/  memmove (void**,void**,int) ; 

void hb_list_rem( hb_list_t * l, void * p )
{
    int i;

    /* Find the item in the list */
    for( i = 0; i < l->items_count; i++ )
    {
        if( l->items[i] == p )
        {
            /* Shift all items after it sizeof( void * ) bytes earlier */
            memmove( &l->items[i], &l->items[i+1],
                     ( l->items_count - i - 1 ) * sizeof( void * ) );

            (l->items_count)--;
            break;
        }
    }
}