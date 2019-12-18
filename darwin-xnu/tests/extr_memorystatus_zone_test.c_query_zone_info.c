#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_5__ {int num_zones; TYPE_1__* zone_names; } ;
struct TYPE_4__ {int /*<<< orphan*/  mzn_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  T_ASSERT_MACH_SUCCESS (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  T_QUIET ; 
 TYPE_3__ current_test ; 
 int /*<<< orphan*/  largest_zone_info ; 
 int /*<<< orphan*/  largest_zone_name ; 
 int /*<<< orphan*/  mach_error_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_host_self () ; 
 int /*<<< orphan*/  mach_zone_info_for_largest_zone (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mach_zone_info_for_zone (int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_zone_info (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zone_info_array ; 

__attribute__((used)) static void query_zone_info(void)
{
	int i;
	kern_return_t kr;
	static uint64_t num_calls = 0;

	for (i = 0; i < current_test.num_zones; i++) {
		kr = mach_zone_info_for_zone(mach_host_self(), current_test.zone_names[i], &(zone_info_array[i]));
		T_QUIET; T_ASSERT_MACH_SUCCESS(kr, "mach_zone_info_for_zone(%s) returned %d [%s]", current_test.zone_names[i].mzn_name, kr, mach_error_string(kr));
	}
	kr = mach_zone_info_for_largest_zone(mach_host_self(), &largest_zone_name, &largest_zone_info);
	T_QUIET; T_ASSERT_MACH_SUCCESS(kr, "mach_zone_info_for_largest_zone returned %d [%s]", kr, mach_error_string(kr));

	num_calls++;
	if (num_calls % 10 != 0) {
		return;
	}

	/* Print out size and element count for zones relevant to the test */
	for (i = 0; i < current_test.num_zones; i++) {
		print_zone_info(&(current_test.zone_names[i]), &(zone_info_array[i]));
	}
}