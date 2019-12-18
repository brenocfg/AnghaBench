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
struct kcdata_descriptor {scalar_t__ kcd_addr_begin; } ;
typedef  TYPE_1__* os_reason_t ;
typedef  scalar_t__ mach_vm_address_t ;
struct TYPE_4__ {struct kcdata_descriptor osr_kcd_descriptor; int /*<<< orphan*/ * osr_kcd_buf; } ;

/* Variables and functions */
 TYPE_1__* OS_REASON_NULL ; 
 int /*<<< orphan*/  assert (int) ; 

struct kcdata_descriptor *
os_reason_get_kcdata_descriptor(os_reason_t cur_reason)
{
	if (cur_reason == OS_REASON_NULL) {
		return NULL;
	}

	if (cur_reason->osr_kcd_buf == NULL) {
		return NULL;
	}

	assert(cur_reason->osr_kcd_descriptor.kcd_addr_begin == (mach_vm_address_t) cur_reason->osr_kcd_buf);
	if (cur_reason->osr_kcd_descriptor.kcd_addr_begin != (mach_vm_address_t) cur_reason->osr_kcd_buf) {
		return NULL;
	}

	return &cur_reason->osr_kcd_descriptor;
}