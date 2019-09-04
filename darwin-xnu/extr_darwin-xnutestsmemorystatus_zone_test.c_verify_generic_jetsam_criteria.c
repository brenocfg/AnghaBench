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
struct TYPE_3__ {int /*<<< orphan*/  mzn_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  T_LOG (char*) ; 
 int /*<<< orphan*/  VME_ZONE ; 
 int /*<<< orphan*/  VMOBJECTS_ZONE ; 
 int /*<<< orphan*/  largest_zone_info ; 
 TYPE_1__ largest_zone_name ; 
 int /*<<< orphan*/  print_zone_info (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vme_zone_compares_to_vm_objects () ; 

__attribute__((used)) static bool verify_generic_jetsam_criteria(void)
{
	T_LOG("Largest zone info");
	print_zone_info(&largest_zone_name, &largest_zone_info);

	/* If VM map entries is not the largest zone */
	if (strcmp(largest_zone_name.mzn_name, VME_ZONE)) {
		/* If vm objects is the largest zone and the VM map entries zone had comparable # of elements, return false */
		if (!strcmp(largest_zone_name.mzn_name, VMOBJECTS_ZONE) && vme_zone_compares_to_vm_objects()) {
			return false;
		}
		return true;
	}
	return false;
}