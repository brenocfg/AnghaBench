#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct x86_cpu_id {int vendor; int family; int model; int feature; } ;
struct cpuinfo_x86 {int x86_vendor; int x86; int x86_model; } ;

/* Variables and functions */
 int X86_FAMILY_ANY ; 
 int X86_FEATURE_ANY ; 
 int X86_MODEL_ANY ; 
 int X86_VENDOR_ANY ; 
 struct cpuinfo_x86 boot_cpu_data ; 
 int /*<<< orphan*/  cpu_has (struct cpuinfo_x86*,int) ; 

const struct x86_cpu_id *x86_match_cpu(const struct x86_cpu_id *match)
{
	const struct x86_cpu_id *m;
	struct cpuinfo_x86 *c = &boot_cpu_data;

	for (m = match; m->vendor | m->family | m->model | m->feature; m++) {
		if (m->vendor != X86_VENDOR_ANY && c->x86_vendor != m->vendor)
			continue;
		if (m->family != X86_FAMILY_ANY && c->x86 != m->family)
			continue;
		if (m->model != X86_MODEL_ANY && c->x86_model != m->model)
			continue;
		if (m->feature != X86_FEATURE_ANY && !cpu_has(c, m->feature))
			continue;
		return m;
	}
	return NULL;
}