#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int cpuid_family; int /*<<< orphan*/  cpuid_cpufamily; int /*<<< orphan*/  cpuid_model; } ;
typedef  TYPE_1__ i386_cpu_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFAMILY_INTEL_BROADWELL ; 
 int /*<<< orphan*/  CPUFAMILY_INTEL_HASWELL ; 
 int /*<<< orphan*/  CPUFAMILY_INTEL_IVYBRIDGE ; 
 int /*<<< orphan*/  CPUFAMILY_INTEL_KABYLAKE ; 
 int /*<<< orphan*/  CPUFAMILY_INTEL_NEHALEM ; 
 int /*<<< orphan*/  CPUFAMILY_INTEL_PENRYN ; 
 int /*<<< orphan*/  CPUFAMILY_INTEL_SANDYBRIDGE ; 
 int /*<<< orphan*/  CPUFAMILY_INTEL_SKYLAKE ; 
 int /*<<< orphan*/  CPUFAMILY_INTEL_WESTMERE ; 
 int /*<<< orphan*/  CPUFAMILY_UNKNOWN ; 
#define  CPUID_MODEL_BROADWELL 149 
#define  CPUID_MODEL_BRYSTALWELL 148 
#define  CPUID_MODEL_CRYSTALWELL 147 
#define  CPUID_MODEL_DALES 146 
#define  CPUID_MODEL_DALES_32NM 145 
#define  CPUID_MODEL_FIELDS 144 
#define  CPUID_MODEL_HASWELL 143 
#define  CPUID_MODEL_HASWELL_EP 142 
#define  CPUID_MODEL_HASWELL_ULT 141 
#define  CPUID_MODEL_IVYBRIDGE 140 
#define  CPUID_MODEL_IVYBRIDGE_EP 139 
#define  CPUID_MODEL_JAKETOWN 138 
#define  CPUID_MODEL_KABYLAKE 137 
#define  CPUID_MODEL_KABYLAKE_DT 136 
#define  CPUID_MODEL_NEHALEM 135 
#define  CPUID_MODEL_NEHALEM_EX 134 
#define  CPUID_MODEL_SANDYBRIDGE 133 
#define  CPUID_MODEL_SKYLAKE 132 
#define  CPUID_MODEL_SKYLAKE_DT 131 
#define  CPUID_MODEL_SKYLAKE_W 130 
#define  CPUID_MODEL_WESTMERE 129 
#define  CPUID_MODEL_WESTMERE_EX 128 
 int /*<<< orphan*/  DBG (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
cpuid_set_cpufamily(i386_cpu_info_t *info_p)
{
	uint32_t cpufamily = CPUFAMILY_UNKNOWN;

	switch (info_p->cpuid_family) {
	case 6:
		switch (info_p->cpuid_model) {
		case 23:
			cpufamily = CPUFAMILY_INTEL_PENRYN;
			break;
		case CPUID_MODEL_NEHALEM:
		case CPUID_MODEL_FIELDS:
		case CPUID_MODEL_DALES:
		case CPUID_MODEL_NEHALEM_EX:
			cpufamily = CPUFAMILY_INTEL_NEHALEM;
			break;
		case CPUID_MODEL_DALES_32NM:
		case CPUID_MODEL_WESTMERE:
		case CPUID_MODEL_WESTMERE_EX:
			cpufamily = CPUFAMILY_INTEL_WESTMERE;
			break;
		case CPUID_MODEL_SANDYBRIDGE:
		case CPUID_MODEL_JAKETOWN:
			cpufamily = CPUFAMILY_INTEL_SANDYBRIDGE;
			break;
		case CPUID_MODEL_IVYBRIDGE:
		case CPUID_MODEL_IVYBRIDGE_EP:
			cpufamily = CPUFAMILY_INTEL_IVYBRIDGE;
			break;
		case CPUID_MODEL_HASWELL:
		case CPUID_MODEL_HASWELL_EP:
		case CPUID_MODEL_HASWELL_ULT:
		case CPUID_MODEL_CRYSTALWELL:
			cpufamily = CPUFAMILY_INTEL_HASWELL;
			break;
		case CPUID_MODEL_BROADWELL:
		case CPUID_MODEL_BRYSTALWELL:
			cpufamily = CPUFAMILY_INTEL_BROADWELL;
			break;
		case CPUID_MODEL_SKYLAKE:
		case CPUID_MODEL_SKYLAKE_DT:
#if !defined(RC_HIDE_XNU_J137)
		case CPUID_MODEL_SKYLAKE_W:
#endif
			cpufamily = CPUFAMILY_INTEL_SKYLAKE;
			break;
               case CPUID_MODEL_KABYLAKE:
               case CPUID_MODEL_KABYLAKE_DT:
                       cpufamily = CPUFAMILY_INTEL_KABYLAKE;
                       break;
		}
		break;
	}

	info_p->cpuid_cpufamily = cpufamily;
	DBG("cpuid_set_cpufamily(%p) returning 0x%x\n", info_p, cpufamily);
	return cpufamily;
}