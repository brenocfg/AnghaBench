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
struct TYPE_4__ {struct TYPE_4__* items; } ;
typedef  TYPE_1__ hb_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void hb_list_close( hb_list_t ** _l )
{
    hb_list_t * l = *_l;

    if (l == NULL)
    {
        return;
    }

    free( l->items );
    free( l );

    *_l = NULL;
}