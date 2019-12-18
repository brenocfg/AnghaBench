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
struct TYPE_4__ {int format; char const* short_name; } ;
typedef  TYPE_1__ hb_container_t ;

/* Variables and functions */
 int HB_MUX_MASK ; 
 TYPE_1__* hb_container_get_next (TYPE_1__ const*) ; 

const char* hb_container_get_short_name(int format)
{
    if (!(format & HB_MUX_MASK))
        goto fail;

    const hb_container_t *container = NULL;
    while ((container = hb_container_get_next(container)) != NULL)
    {
        if (container->format == format)
        {
            return container->short_name;
        }
    }

fail:
    return NULL;
}