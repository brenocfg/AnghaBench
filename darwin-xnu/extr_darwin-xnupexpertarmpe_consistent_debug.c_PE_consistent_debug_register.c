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
typedef  void* uint64_t ;
struct TYPE_3__ {void* record_id; void* physaddr; void* length; } ;
typedef  TYPE_1__ dbg_record_header_t ;

/* Variables and functions */
 TYPE_1__* consistent_debug_allocate_entry () ; 

int PE_consistent_debug_register(uint64_t record_id, uint64_t physaddr, uint64_t length)
{
	dbg_record_header_t *allocated_header = consistent_debug_allocate_entry();
	if (allocated_header == NULL)
		return -1;
	allocated_header->length = length;
	allocated_header->physaddr = physaddr;
	// Make sure the hdr/length are visible before the record_id.
	__asm__ volatile("dmb ish" : : : "memory");
	allocated_header->record_id = record_id;
	return 0;
}