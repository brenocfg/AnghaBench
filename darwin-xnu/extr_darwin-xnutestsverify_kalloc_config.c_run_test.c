#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  vm_address_t ;
typedef  unsigned int uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/ * mzn_name; } ;
typedef  TYPE_1__ mach_zone_name_t ;
struct TYPE_6__ {unsigned int mzi_elem_size; } ;
typedef  TYPE_2__ mach_zone_info_t ;
typedef  int /*<<< orphan*/  mach_memory_info_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  T_ASSERT_EQ (unsigned int,unsigned int,char*) ; 
 int /*<<< orphan*/  T_ASSERT_MACH_SUCCESS (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_END ; 
 int /*<<< orphan*/  T_LOG (char*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  mach_host_self () ; 
 int /*<<< orphan*/  mach_memory_info (int /*<<< orphan*/ ,TYPE_1__**,unsigned int*,TYPE_2__**,unsigned int*,int /*<<< orphan*/ **,unsigned int*) ; 
 int /*<<< orphan*/  mach_task_self () ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ *,char const*,size_t) ; 
 unsigned int strtoul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vm_deallocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void run_test(void)
{
	kern_return_t kr;
	uint64_t size, i;
	mach_zone_name_t *name = NULL;
	unsigned int nameCnt = 0;
	mach_zone_info_t *info = NULL;
	unsigned int infoCnt = 0;
	mach_memory_info_t *wiredInfo = NULL;
	unsigned int wiredInfoCnt = 0;
	const char kalloc_str[] = "kalloc.";

	kr = mach_memory_info(mach_host_self(),
			&name, &nameCnt, &info, &infoCnt,
			&wiredInfo, &wiredInfoCnt);
	T_QUIET; T_ASSERT_MACH_SUCCESS(kr, "mach_memory_info");
	T_QUIET; T_ASSERT_EQ(nameCnt, infoCnt, "zone name and info counts don't match");

	/* Match the names of the kalloc zones against their element sizes. */
	for (i = 0; i < nameCnt; i++) {
		if (strncmp(name[i].mzn_name, kalloc_str, strlen(kalloc_str)) == 0) {
			size = strtoul(&(name[i].mzn_name[strlen(kalloc_str)]), NULL, 10);
			T_LOG("ZONE NAME: %-25s ELEMENT SIZE: %llu", name[i].mzn_name, size);
			T_QUIET; T_ASSERT_EQ(size, info[i].mzi_elem_size, "kalloc zone name and element size don't match");
		}
	}

	if ((name != NULL) && (nameCnt != 0)) {
		kr = vm_deallocate(mach_task_self(), (vm_address_t) name,
				(vm_size_t) (nameCnt * sizeof *name));
		T_QUIET; T_ASSERT_MACH_SUCCESS(kr, "vm_deallocate name");
	}

	if ((info != NULL) && (infoCnt != 0)) {
		kr = vm_deallocate(mach_task_self(), (vm_address_t) info,
				(vm_size_t) (infoCnt * sizeof *info));
		T_QUIET; T_ASSERT_MACH_SUCCESS(kr, "vm_deallocate info");
	}

	if ((wiredInfo != NULL) && (wiredInfoCnt != 0)) {
		kr = vm_deallocate(mach_task_self(), (vm_address_t) wiredInfo,
				(vm_size_t) (wiredInfoCnt * sizeof *wiredInfo));
		T_QUIET; T_ASSERT_MACH_SUCCESS(kr, "vm_deallocate wiredInfo");
	}

	T_END;
}