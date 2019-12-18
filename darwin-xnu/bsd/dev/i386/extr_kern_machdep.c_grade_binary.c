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
#define  CPU_SUBTYPE_X86_64_ALL 132 
#define  CPU_SUBTYPE_X86_64_H 131 
#define  CPU_SUBTYPE_X86_ARCH1 130 
#define  CPU_TYPE_X86 129 
#define  CPU_TYPE_X86_64 128 
 int /*<<< orphan*/  cpu_subtype () ; 

int
grade_binary(cpu_type_t exectype, cpu_subtype_t execsubtype)
{
	cpu_subtype_t hostsubtype = cpu_subtype();

	switch(exectype) {
	case CPU_TYPE_X86_64:		/* native 64-bit */
		switch(hostsubtype) {
		case CPU_SUBTYPE_X86_64_H:	/* x86_64h can execute anything */
			switch (execsubtype) {
			case CPU_SUBTYPE_X86_64_H:
				return 3;
			case CPU_SUBTYPE_X86_64_ALL:
				return 2;
			}
			break;
		case CPU_SUBTYPE_X86_ARCH1:	/* generic systems can only execute ALL subtype */
			switch (execsubtype) {
			case CPU_SUBTYPE_X86_64_ALL:
				return 2;
			}
			break;
		}
		break;
	case CPU_TYPE_X86:		/* native */
		return 1;
	}

	return 0;
}