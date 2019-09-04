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
typedef  int /*<<< orphan*/  vm_map_entry_t ;
struct vm_map_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _vm_map_entry_link_ll (struct vm_map_header*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
vm_map_store_entry_link_ll( struct vm_map_header *mapHdr, vm_map_entry_t after_where, vm_map_entry_t entry)
{
	_vm_map_entry_link_ll( mapHdr, after_where, entry);
}