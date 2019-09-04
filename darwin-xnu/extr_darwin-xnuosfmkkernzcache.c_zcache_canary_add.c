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
typedef  TYPE_1__* zone_t ;
typedef  uintptr_t vm_offset_t ;
struct TYPE_3__ {uintptr_t elem_size; } ;

/* Variables and functions */
 uintptr_t zcache_canary ; 

void zcache_canary_add(zone_t zone, void *element)
{
	vm_offset_t *primary = (vm_offset_t *)element;
	vm_offset_t *backup = (vm_offset_t *)((vm_offset_t)primary + zone->elem_size - sizeof(vm_offset_t));
	*primary = *backup = (zcache_canary ^ (uintptr_t)element);
}