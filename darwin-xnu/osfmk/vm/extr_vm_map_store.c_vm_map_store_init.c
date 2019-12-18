#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vm_map_header {int dummy; } ;

/* Variables and functions */
 scalar_t__ vm_map_store_has_RB_support (struct vm_map_header*) ; 
 int /*<<< orphan*/  vm_map_store_init_ll (struct vm_map_header*) ; 
 int /*<<< orphan*/  vm_map_store_init_rb (struct vm_map_header*) ; 

void
vm_map_store_init( struct vm_map_header *hdr )
{
	vm_map_store_init_ll( hdr );
#ifdef VM_MAP_STORE_USE_RB
	if (vm_map_store_has_RB_support( hdr )) {
		vm_map_store_init_rb( hdr );
	}
#endif
}