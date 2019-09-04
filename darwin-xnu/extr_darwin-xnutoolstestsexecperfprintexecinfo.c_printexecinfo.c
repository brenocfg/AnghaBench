#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  stackaddr ;
struct TYPE_5__ {int cputype; int cpusubtype; } ;
struct TYPE_4__ {char* name; char* description; } ;
typedef  TYPE_1__ NXArchInfo ;

/* Variables and functions */
 int CPU_SUBTYPE_MASK ; 
 TYPE_1__* NXGetArchInfoFromCpuType (int,int) ; 
 TYPE_2__ _mh_execute_header ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int sysctlbyname (char*,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void printexecinfo(void)
{
	int ret;
	uint64_t stackaddr;
	size_t len = sizeof(stackaddr);
	const NXArchInfo *arch = NXGetArchInfoFromCpuType(_mh_execute_header.cputype, _mh_execute_header.cpusubtype & ~CPU_SUBTYPE_MASK);

	printf("executable load address = 0x%016llx\n", (uint64_t)(uintptr_t)&_mh_execute_header);
	printf("executable cputype 0x%08x cpusubtype 0x%08x (%s:%s)\n",
		   _mh_execute_header.cputype,
		   _mh_execute_header.cpusubtype,
		   arch ? arch->name : "unknown",
		   arch ? arch->description : "unknown");

	ret = sysctlbyname("kern.usrstack64", &stackaddr, &len, NULL, 0);
	if (ret == -1)
		err(1, "sysctlbyname");

	printf("          stack address = 0x%016llx\n", stackaddr);
}