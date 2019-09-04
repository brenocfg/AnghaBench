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
typedef  int /*<<< orphan*/  pmap_t ;
typedef  scalar_t__ mach_vm_size_t ;
typedef  scalar_t__ mach_vm_address_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_3__ {int /*<<< orphan*/  pmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  pmap_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_page_64 (scalar_t__) ; 
 int /*<<< orphan*/  trunc_page_64 (scalar_t__) ; 

kern_return_t IOUnmapPages(vm_map_t map, mach_vm_address_t va, mach_vm_size_t length)
{
    pmap_t	pmap = map->pmap;

    pmap_remove(pmap, trunc_page_64(va), round_page_64(va + length));

    return( KERN_SUCCESS );
}