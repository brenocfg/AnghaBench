#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* sub_filter; scalar_t__ settings; } ;
typedef  TYPE_1__ hb_filter_object_t ;

/* Variables and functions */
 scalar_t__ hb_value_dup (scalar_t__) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 

hb_filter_object_t * hb_filter_copy( hb_filter_object_t * filter )
{
    if( filter == NULL )
        return NULL;

    hb_filter_object_t * filter_copy = malloc( sizeof( hb_filter_object_t ) );
    memcpy( filter_copy, filter, sizeof( hb_filter_object_t ) );
    if( filter->settings )
        filter_copy->settings = hb_value_dup(filter->settings);
    filter_copy->sub_filter = hb_filter_copy(filter->sub_filter);
    return filter_copy;
}