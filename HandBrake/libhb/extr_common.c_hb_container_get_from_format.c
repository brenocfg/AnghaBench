#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int format; } ;
typedef  TYPE_1__ hb_container_t ;
struct TYPE_5__ {TYPE_1__ item; } ;

/* Variables and functions */
 TYPE_2__* hb_containers ; 
 int hb_containers_count ; 

hb_container_t* hb_container_get_from_format(int format)
{
    int i;
    for (i = 0; i < hb_containers_count; i++)
    {
        if (hb_containers[i].item.format == format)
        {
            return &hb_containers[i].item;
        }
    }

    return NULL;
}