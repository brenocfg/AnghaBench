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
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int cpuid_cores_per_package; int cpuid_logical_per_package; } ;

/* Variables and functions */
 int CPUID_FEATURE_HTT ; 
 TYPE_1__* cpuid_cpu_infop ; 
 int cpuid_features () ; 
 int /*<<< orphan*/  cpuid_get_feature_names (int,char*,int) ; 
 int /*<<< orphan*/  cpuid_get_leaf7_feature_names (scalar_t__,char*,int) ; 
 scalar_t__ cpuid_leaf7_features () ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 

void
cpuid_feature_display(
	const char	*header)
{
       char    buf[320];

	kprintf("%s: %s", header,
		 cpuid_get_feature_names(cpuid_features(), buf, sizeof(buf)));
	if (cpuid_leaf7_features())
		kprintf(" %s", cpuid_get_leaf7_feature_names(
				cpuid_leaf7_features(), buf, sizeof(buf)));
	kprintf("\n");
	if (cpuid_features() & CPUID_FEATURE_HTT) {
#define s_if_plural(n)	((n > 1) ? "s" : "")
		kprintf("  HTT: %d core%s per package;"
			     " %d logical cpu%s per package\n",
			cpuid_cpu_infop->cpuid_cores_per_package,
			s_if_plural(cpuid_cpu_infop->cpuid_cores_per_package),
			cpuid_cpu_infop->cpuid_logical_per_package,
			s_if_plural(cpuid_cpu_infop->cpuid_logical_per_package));
	}
}