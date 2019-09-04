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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
#define  CPU_SUBTYPE_ARM_V7K 129 
#define  CPU_TYPE_ARM 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

boolean_t
pie_required(cpu_type_t exectype, cpu_subtype_t execsubtype)
{
	switch (exectype) {
#if __arm64__
	case CPU_TYPE_ARM64:
		return TRUE;
#endif /* __arm64__ */

	case CPU_TYPE_ARM:
		switch (execsubtype) {
			case CPU_SUBTYPE_ARM_V7K:
				return TRUE;
			}
		break;
	}
	return FALSE;
}