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
typedef  TYPE_1__* vm_map_t ;
struct TYPE_3__ {int /*<<< orphan*/  map_disallow_data_exec; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 

void
vm_map_disallow_data_exec(vm_map_t map)
{
    if (map == NULL)
        return;

    map->map_disallow_data_exec = TRUE;
}