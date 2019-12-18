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
typedef  int boolean_t ;
struct TYPE_3__ {scalar_t__ pmap; } ;

/* Variables and functions */
 scalar_t__ kernel_pmap ; 

boolean_t
vm_kernel_map_is_kernel(vm_map_t map) {
	return (map->pmap == kernel_pmap);
}