#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* vm_named_entry_t ;
struct TYPE_8__ {int /*<<< orphan*/  map; } ;
struct TYPE_12__ {TYPE_1__ backing; } ;
struct TYPE_9__ {int /*<<< orphan*/  map; } ;
struct TYPE_11__ {TYPE_2__ backing; } ;
struct TYPE_10__ {scalar_t__ ip_kobject; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHARED_REGION_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  _COMM_PAGE32_AREA_LENGTH ; 
 int /*<<< orphan*/  _COMM_PAGE64_AREA_LENGTH ; 
 int __commpage_setup ; 
 scalar_t__ __system_power_source ; 
 int /*<<< orphan*/  _vm_commpage_init (TYPE_3__**,int /*<<< orphan*/ ) ; 
 TYPE_6__* commpage32_entry ; 
 TYPE_3__* commpage32_handle ; 
 int /*<<< orphan*/  commpage32_map ; 
 TYPE_4__* commpage64_entry ; 
 TYPE_3__* commpage64_handle ; 
 int /*<<< orphan*/  commpage64_map ; 
 int /*<<< orphan*/  commpage_populate () ; 
 int /*<<< orphan*/  post_sys_powersource_internal (int /*<<< orphan*/ ,int) ; 

void
vm_commpage_init(void)
{
	SHARED_REGION_TRACE_DEBUG(
		("commpage: -> init()\n"));

#if defined(__i386__) || defined(__x86_64__)
	/* create the 32-bit comm page */
	_vm_commpage_init(&commpage32_handle, _COMM_PAGE32_AREA_LENGTH);
	commpage32_entry = (vm_named_entry_t) commpage32_handle->ip_kobject;
	commpage32_map = commpage32_entry->backing.map;

	/* XXX if (cpu_is_64bit_capable()) ? */
	/* create the 64-bit comm page */
	_vm_commpage_init(&commpage64_handle, _COMM_PAGE64_AREA_LENGTH);
	commpage64_entry = (vm_named_entry_t) commpage64_handle->ip_kobject;
	commpage64_map = commpage64_entry->backing.map;

#endif /* __i386__ || __x86_64__ */

	/* populate them according to this specific platform */
	commpage_populate();
	__commpage_setup = 1;
#if defined(__i386__) || defined(__x86_64__)
	if (__system_power_source == 0) {
		post_sys_powersource_internal(0, 1);
	}
#endif /* __i386__ || __x86_64__ */

	SHARED_REGION_TRACE_DEBUG(
		("commpage: init() <-\n"));
}