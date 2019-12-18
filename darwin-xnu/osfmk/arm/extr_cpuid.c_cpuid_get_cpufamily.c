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
struct TYPE_3__ {int arm_implementor; int /*<<< orphan*/  arm_part; } ;
struct TYPE_4__ {TYPE_1__ arm_info; } ;

/* Variables and functions */
 int CPUFAMILY_ARM_11 ; 
 int CPUFAMILY_ARM_13 ; 
 int CPUFAMILY_ARM_14 ; 
 int CPUFAMILY_ARM_15 ; 
 int CPUFAMILY_ARM_9 ; 
 int CPUFAMILY_ARM_CYCLONE ; 
 int CPUFAMILY_ARM_HURRICANE ; 
 int CPUFAMILY_ARM_MONSOON_MISTRAL ; 
 int CPUFAMILY_ARM_SWIFT ; 
 int CPUFAMILY_ARM_TWISTER ; 
 int CPUFAMILY_ARM_TYPHOON ; 
 int CPUFAMILY_ARM_XSCALE ; 
 int CPUFAMILY_UNKNOWN ; 
#define  CPU_PART_1136JFS 147 
#define  CPU_PART_1176JZFS 146 
#define  CPU_PART_920T 145 
#define  CPU_PART_926EJS 144 
#define  CPU_PART_CORTEXA7 143 
#define  CPU_PART_CORTEXA8 142 
#define  CPU_PART_CORTEXA9 141 
#define  CPU_PART_CYCLONE 140 
#define  CPU_PART_HURRICANE 139 
#define  CPU_PART_HURRICANE_MYST 138 
#define  CPU_PART_MISTRAL 137 
#define  CPU_PART_MONSOON 136 
#define  CPU_PART_SWIFT 135 
#define  CPU_PART_TWISTER 134 
#define  CPU_PART_TWISTER_ELBA_MALTA 133 
#define  CPU_PART_TYPHOON 132 
#define  CPU_PART_TYPHOON_CAPRI 131 
#define  CPU_VID_APPLE 130 
#define  CPU_VID_ARM 129 
#define  CPU_VID_INTEL 128 
 TYPE_2__* cpuid_info () ; 

int
cpuid_get_cpufamily(void)
{
	int cpufamily = 0;

	switch (cpuid_info()->arm_info.arm_implementor) {
	case CPU_VID_ARM:
		switch (cpuid_info()->arm_info.arm_part) {
		case CPU_PART_CORTEXA9:
			cpufamily = CPUFAMILY_ARM_14;
			break;
		case CPU_PART_CORTEXA8:
			cpufamily = CPUFAMILY_ARM_13;
			break;
		case CPU_PART_CORTEXA7:
			cpufamily = CPUFAMILY_ARM_15;
			break;
		case CPU_PART_1136JFS:
		case CPU_PART_1176JZFS:
			cpufamily = CPUFAMILY_ARM_11;
			break;
		case CPU_PART_926EJS:
		case CPU_PART_920T:
			cpufamily = CPUFAMILY_ARM_9;
			break;
		default:
			cpufamily = CPUFAMILY_UNKNOWN;
			break;
		}
		break;

	case CPU_VID_INTEL:
		cpufamily = CPUFAMILY_ARM_XSCALE;
		break;

	case CPU_VID_APPLE:
		switch (cpuid_info()->arm_info.arm_part) {
		case CPU_PART_SWIFT:
			cpufamily = CPUFAMILY_ARM_SWIFT;
			break;
		case CPU_PART_CYCLONE:
			cpufamily = CPUFAMILY_ARM_CYCLONE;
			break;
		case CPU_PART_TYPHOON:
		case CPU_PART_TYPHOON_CAPRI:
			cpufamily = CPUFAMILY_ARM_TYPHOON;
			break;
		case CPU_PART_TWISTER:
		case CPU_PART_TWISTER_ELBA_MALTA:
			cpufamily = CPUFAMILY_ARM_TWISTER;
			break;
		case CPU_PART_HURRICANE:
		case CPU_PART_HURRICANE_MYST:
			cpufamily = CPUFAMILY_ARM_HURRICANE;
			break;
		case CPU_PART_MONSOON:
		case CPU_PART_MISTRAL:
			cpufamily = CPUFAMILY_ARM_MONSOON_MISTRAL;
			break;
		default:
			cpufamily = CPUFAMILY_UNKNOWN;
			break;
		}
		break;

	default:
		cpufamily = CPUFAMILY_UNKNOWN;
		break;
	}

	return cpufamily;
}