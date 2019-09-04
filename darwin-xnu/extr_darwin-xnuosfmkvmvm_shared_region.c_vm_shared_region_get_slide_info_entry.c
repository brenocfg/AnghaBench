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
typedef  TYPE_2__* vm_shared_region_t ;
struct TYPE_4__ {scalar_t__ slide_info_entry; } ;
struct TYPE_5__ {TYPE_1__ sr_slide_info; } ;

/* Variables and functions */

void* 
vm_shared_region_get_slide_info_entry(vm_shared_region_t sr) {
	return (void*)sr->sr_slide_info.slide_info_entry;
}