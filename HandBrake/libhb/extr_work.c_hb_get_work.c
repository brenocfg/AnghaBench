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
struct TYPE_5__ {int id; int /*<<< orphan*/ * h; struct TYPE_5__* next; } ;
typedef  TYPE_1__ hb_work_object_t ;
typedef  int /*<<< orphan*/  hb_handle_t ;

/* Variables and functions */
 TYPE_1__* hb_objects ; 
 TYPE_1__* malloc (int) ; 

hb_work_object_t * hb_get_work( hb_handle_t *h, int id )
{
    hb_work_object_t * w;
    for( w = hb_objects; w; w = w->next )
    {
        if( w->id == id )
        {
            hb_work_object_t *wc = malloc( sizeof(*w) );
            *wc = *w;
            wc->h = h;
            return wc;
        }
    }
    return NULL;
}