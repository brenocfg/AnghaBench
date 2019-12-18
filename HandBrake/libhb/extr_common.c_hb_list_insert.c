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
struct TYPE_3__ {int items_count; int items_alloc; void** items; } ;
typedef  TYPE_1__ hb_list_t ;

/* Variables and functions */
 scalar_t__ HB_LIST_DEFAULT_SIZE ; 
 int /*<<< orphan*/  memmove (void**,void**,int) ; 
 void** realloc (void**,int) ; 

void hb_list_insert( hb_list_t * l, int pos, void * p )
{
    if( !p )
    {
        return;
    }

    if( l->items_count == l->items_alloc )
    {
        /* We need a bigger boat */
        l->items_alloc += HB_LIST_DEFAULT_SIZE;
        l->items        = realloc( l->items,
                                   l->items_alloc * sizeof( void * ) );
    }

    if ( l->items_count != pos )
    {
        /* Shift all items after it sizeof( void * ) bytes earlier */
        memmove( &l->items[pos+1], &l->items[pos],
                 ( l->items_count - pos ) * sizeof( void * ) );
    }


    l->items[pos] = p;
    (l->items_count)++;
}