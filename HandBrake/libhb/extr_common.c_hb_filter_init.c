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
struct TYPE_4__ {int id; int /*<<< orphan*/  name; struct TYPE_4__* sub_filter; } ;
typedef  TYPE_1__ hb_filter_object_t ;

/* Variables and functions */
#define  HB_FILTER_CHROMA_SMOOTH 130 
#define  HB_FILTER_LAPSHARP 129 
 int HB_FILTER_MT_FRAME ; 
#define  HB_FILTER_UNSHARP 128 
 TYPE_1__* hb_filter_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_filter_get (int) ; 

hb_filter_object_t * hb_filter_init( int filter_id )
{
    switch (filter_id)
    {
        case HB_FILTER_UNSHARP:
        case HB_FILTER_LAPSHARP:
        case HB_FILTER_CHROMA_SMOOTH:
        {
            hb_filter_object_t * wrapper;

            wrapper = hb_filter_copy(hb_filter_get(HB_FILTER_MT_FRAME));
            wrapper->sub_filter = hb_filter_copy(hb_filter_get(filter_id));
            wrapper->id = filter_id;
            wrapper->name = wrapper->sub_filter->name;
            return wrapper;
        } break;

        default:
            return hb_filter_copy(hb_filter_get(filter_id));
    }
}