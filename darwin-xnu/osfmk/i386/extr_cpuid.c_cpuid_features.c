#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  fpu_arg ;
struct TYPE_2__ {int cpuid_features; } ;

/* Variables and functions */
 int CPUID_FEATURE_FXSR ; 
 int CPUID_FEATURE_SSE ; 
 int CPUID_FEATURE_SSE2 ; 
 scalar_t__ PE_parse_boot_argn (char*,char*,int) ; 
 TYPE_1__* cpuid_cpu_infop ; 
 int /*<<< orphan*/  cpuid_info () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

uint64_t
cpuid_features(void)
{
	static int checked = 0;
	char	fpu_arg[20] = { 0 };

	(void) cpuid_info();
	if (!checked) {
		    /* check for boot-time fpu limitations */
			if (PE_parse_boot_argn("_fpu", &fpu_arg[0], sizeof (fpu_arg))) {
				printf("limiting fpu features to: %s\n", fpu_arg);
				if (!strncmp("387", fpu_arg, sizeof("387")) || !strncmp("mmx", fpu_arg, sizeof("mmx"))) {
					printf("no sse or sse2\n");
					cpuid_cpu_infop->cpuid_features &= ~(CPUID_FEATURE_SSE | CPUID_FEATURE_SSE2 | CPUID_FEATURE_FXSR);
				} else if (!strncmp("sse", fpu_arg, sizeof("sse"))) {
					printf("no sse2\n");
					cpuid_cpu_infop->cpuid_features &= ~(CPUID_FEATURE_SSE2);
				}
			}
			checked = 1;
	}
	return cpuid_cpu_infop->cpuid_features;
}