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
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {scalar_t__ elem_size; int /*<<< orphan*/  zone_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,void*,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*,void*) ; 
 scalar_t__ zp_nopoison_cookie ; 
 scalar_t__ zp_poisoned_cookie ; 

__attribute__((used)) static inline void /* noreturn */
zone_element_was_modified_panic(zone_t        zone,
                                vm_offset_t   element,
                                vm_offset_t   found,
                                vm_offset_t   expected,
                                vm_offset_t   offset)
{
	panic("a freed zone element has been modified in zone %s: expected %p but found %p, bits changed %p, at offset %d of %d in element %p, cookies %p %p",
	                 zone->zone_name,
	      (void *)   expected,
	      (void *)   found,
	      (void *)   (expected ^ found),
	      (uint32_t) offset,
	      (uint32_t) zone->elem_size,
	      (void *)   element,
	      (void *)   zp_nopoison_cookie,
	      (void *)   zp_poisoned_cookie);
}