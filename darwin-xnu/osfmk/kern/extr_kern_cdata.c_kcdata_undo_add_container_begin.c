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
struct kcdata_item {int dummy; } ;
typedef  int mach_vm_address_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_1__* kcdata_descriptor_t ;
struct TYPE_4__ {int kcd_flags; int /*<<< orphan*/  kcd_addr_end; } ;

/* Variables and functions */
 int KCFLAG_NO_AUTO_ENDBUFFER ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  kcdata_write_buffer_end (TYPE_1__*) ; 

kern_return_t
kcdata_undo_add_container_begin(kcdata_descriptor_t data)
{
	/*
	 * the payload of a container begin is a single uint64_t.  It is padded out
	 * to 16 bytes.
	 */
	const mach_vm_address_t padded_payload_size = 16;
	data->kcd_addr_end -= sizeof(struct kcdata_item) + padded_payload_size;

	if (!(data->kcd_flags & KCFLAG_NO_AUTO_ENDBUFFER)) {
		/* setup the end header as well */
		return kcdata_write_buffer_end(data);
	} else {
		return KERN_SUCCESS;
	}
}