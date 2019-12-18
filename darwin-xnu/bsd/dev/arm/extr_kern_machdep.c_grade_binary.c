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
typedef  int cpu_type_t ;
typedef  int /*<<< orphan*/  cpu_subtype_t ;

/* Variables and functions */
 int CPU_ARCH_ABI64 ; 
#define  CPU_SUBTYPE_ARM64_ALL 141 
#define  CPU_SUBTYPE_ARM64_V8 140 
#define  CPU_SUBTYPE_ARM_ALL 139 
#define  CPU_SUBTYPE_ARM_V4T 138 
#define  CPU_SUBTYPE_ARM_V5TEJ 137 
#define  CPU_SUBTYPE_ARM_V6 136 
#define  CPU_SUBTYPE_ARM_V7 135 
#define  CPU_SUBTYPE_ARM_V7F 134 
#define  CPU_SUBTYPE_ARM_V7K 133 
#define  CPU_SUBTYPE_ARM_V7S 132 
#define  CPU_SUBTYPE_ARM_V8 131 
#define  CPU_SUBTYPE_ARM_XSCALE 130 
#define  CPU_TYPE_ARM 129 
#define  CPU_TYPE_ARM64 128 
 int /*<<< orphan*/  bootarg_no64exec ; 
 int /*<<< orphan*/  cpu_subtype () ; 
 int /*<<< orphan*/  cpu_subtype32 () ; 

int
grade_binary(cpu_type_t exectype, cpu_subtype_t execsubtype)
{
#if __arm64__
	cpu_subtype_t hostsubtype =
		(exectype & CPU_ARCH_ABI64) ? cpu_subtype() : cpu_subtype32();
#else
	cpu_subtype_t hostsubtype = cpu_subtype();
#endif /* __arm64__ */

	switch (exectype) {
#if __arm64__
	case CPU_TYPE_ARM64:
		if (bootarg_no64exec) return 0;

		switch (hostsubtype) {
		case CPU_SUBTYPE_ARM64_V8:
			switch (execsubtype) {
			case CPU_SUBTYPE_ARM64_V8:
				return 10;
			case CPU_SUBTYPE_ARM64_ALL:
				return 9;
			}
			break;

		} /* switch (hostsubtype) */

#else /* __arm64__ */

	case CPU_TYPE_ARM:
		switch (hostsubtype) {
		/*
		 * For 32-bit ARMv8, try the ARMv8 slice before falling back to Swift.
		 */
		case CPU_SUBTYPE_ARM_V8:
			switch (execsubtype) {
			case CPU_SUBTYPE_ARM_V8:
				return 7;
			}
			goto v7s;

		/*
		 * For Swift and later, we prefer to run a swift slice, but fall back
		 * to v7 as Cortex A9 errata should not apply
		 */
v7s:
		case CPU_SUBTYPE_ARM_V7S:
			switch (execsubtype) {
			case CPU_SUBTYPE_ARM_V7S:
				return 6;
			}
			goto v7;

		/*
		 * For Cortex A7, accept v7k only due to differing ABI
		 */
		case CPU_SUBTYPE_ARM_V7K:
			switch (execsubtype) {
			case CPU_SUBTYPE_ARM_V7K:
				return 6;
			}
			break;	

		/*
		 * For Cortex A9, we prefer the A9 slice, but will run v7 albeit
		 * under the risk of hitting the NEON load/store errata
		 */
		case CPU_SUBTYPE_ARM_V7F:
			switch (execsubtype) {
			case CPU_SUBTYPE_ARM_V7F:
				return 6;
			}
			goto v7;

v7:
		case CPU_SUBTYPE_ARM_V7:
			switch (execsubtype) {
			case CPU_SUBTYPE_ARM_V7:
				return 5;
			}
			// fall through...

		case CPU_SUBTYPE_ARM_V6:
			switch (execsubtype) {
			case CPU_SUBTYPE_ARM_V6:
				return 4;
			}
			// fall through...

		case CPU_SUBTYPE_ARM_V5TEJ:
			switch (execsubtype) {
			case CPU_SUBTYPE_ARM_V5TEJ:
				return 3;
			}
			// fall through

		case CPU_SUBTYPE_ARM_V4T:
			switch (execsubtype) {
			case CPU_SUBTYPE_ARM_V4T:
				return 2;
			case CPU_SUBTYPE_ARM_ALL:
				return 1;
			}
			break;

		case CPU_SUBTYPE_ARM_XSCALE:
			switch (execsubtype) {
			case CPU_SUBTYPE_ARM_XSCALE:
				return 4;
			case CPU_SUBTYPE_ARM_V5TEJ:
				return 3;
			case CPU_SUBTYPE_ARM_V4T:
				return 2;
			case CPU_SUBTYPE_ARM_ALL:
				return 1;
			}
			break;
		}
#endif /* __arm64__ */
	}

	return 0;
}