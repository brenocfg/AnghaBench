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
typedef  int u32 ;
typedef  size_t u16 ;
struct av_decision {int allowed; int auditallow; int auditdeny; } ;
struct TYPE_2__ {unsigned int num_perms; int* perms; } ;

/* Variables and functions */
 TYPE_1__* current_mapping ; 
 size_t current_mapping_size ; 

__attribute__((used)) static void map_decision(u16 tclass, struct av_decision *avd,
			 int allow_unknown)
{
	if (tclass < current_mapping_size) {
		unsigned i, n = current_mapping[tclass].num_perms;
		u32 result;

		for (i = 0, result = 0; i < n; i++) {
			if (avd->allowed & current_mapping[tclass].perms[i])
				result |= 1<<i;
			if (allow_unknown && !current_mapping[tclass].perms[i])
				result |= 1<<i;
		}
		avd->allowed = result;

		for (i = 0, result = 0; i < n; i++)
			if (avd->auditallow & current_mapping[tclass].perms[i])
				result |= 1<<i;
		avd->auditallow = result;

		for (i = 0, result = 0; i < n; i++) {
			if (avd->auditdeny & current_mapping[tclass].perms[i])
				result |= 1<<i;
			if (!allow_unknown && !current_mapping[tclass].perms[i])
				result |= 1<<i;
		}
		/*
		 * In case the kernel has a bug and requests a permission
		 * between num_perms and the maximum permission number, we
		 * should audit that denial
		 */
		for (; i < (sizeof(u32)*8); i++)
			result |= 1<<i;
		avd->auditdeny = result;
	}
}