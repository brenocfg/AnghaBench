#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* cpuid; } ;
struct TYPE_4__ {TYPE_1__ env; } ;
struct perf_session {TYPE_2__ header; } ;

/* Variables and functions */
 int ENOTSUP ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 
 scalar_t__ strstr (char*,char*) ; 

__attribute__((used)) static int get_cpu_isa(struct perf_session *session)
{
	char *cpuid = session->header.env.cpuid;
	int isa;

	if (strstr(cpuid, "Intel"))
		isa = 1;
	else if (strstr(cpuid, "AMD"))
		isa = 0;
	else {
		pr_err("CPU %s is not supported.\n", cpuid);
		isa = -ENOTSUP;
	}

	return isa;
}