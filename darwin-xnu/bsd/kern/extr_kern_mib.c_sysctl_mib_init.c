#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  neon_fp16; int /*<<< orphan*/  neon_hpfp; int /*<<< orphan*/  neon; } ;
typedef  TYPE_1__ arm_mvfp_info_t ;
struct TYPE_9__ {int /*<<< orphan*/  num_breakpoint_pairs; int /*<<< orphan*/  num_watchpoint_pairs; } ;
struct TYPE_8__ {scalar_t__ c_l2size; scalar_t__ c_dsize; } ;
struct TYPE_7__ {int thread_count; } ;

/* Variables and functions */
 int CPU_ARCH_ABI64 ; 
 scalar_t__ CPU_THREADTYPE_NONE ; 
 int _get_cpu_capabilities () ; 
 TYPE_5__* arm_debug_info () ; 
 TYPE_1__* arm_mvfp_info () ; 
 int /*<<< orphan*/  breakpoint_flag ; 
 TYPE_3__* cache_info () ; 
 int* cacheconfig ; 
 scalar_t__* cachesize ; 
 int cpu64bit ; 
 int /*<<< orphan*/  cpu_subtype () ; 
 scalar_t__ cpu_threadtype () ; 
 int cpu_type () ; 
 int /*<<< orphan*/  cpufamily ; 
 int /*<<< orphan*/  cpuid_cpufamily () ; 
 int /*<<< orphan*/  cpuid_get_cpufamily () ; 
 TYPE_2__* cpuid_info () ; 
 int /*<<< orphan*/  cpusubtype ; 
 scalar_t__ cputhreadtype ; 
 int cputype ; 
 int /*<<< orphan*/  gNeon ; 
 int /*<<< orphan*/  gNeonFp16 ; 
 int /*<<< orphan*/  gNeonHpfp ; 
 int k64Bit ; 
 int ml_cpu_cache_sharing (int) ; 
 scalar_t__ ml_cpu_cache_size (int) ; 
 scalar_t__ ml_get_machine_mem () ; 
 int ml_get_max_cpus () ; 
 int packages ; 
 int roundup (int,int) ; 
 int /*<<< orphan*/  sysctl__hw_cputhreadtype ; 
 int /*<<< orphan*/  sysctl_register_oid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchpoint_flag ; 

void
sysctl_mib_init(void)
{
	cputype = cpu_type();
	cpusubtype = cpu_subtype();
	cputhreadtype = cpu_threadtype();
#if defined(__i386__) || defined (__x86_64__)
	cpu64bit = (_get_cpu_capabilities() & k64Bit) == k64Bit;
#elif defined(__arm__) || defined (__arm64__)
	cpu64bit = (cputype & CPU_ARCH_ABI64) == CPU_ARCH_ABI64;
#else
#error Unsupported arch
#endif

	/*
	 * Populate the optional portion of the hw.* MIB.
	 *
	 * XXX This could be broken out into parts of the code
	 *     that actually directly relate to the functions in
	 *     question.
	 */

	if (cputhreadtype != CPU_THREADTYPE_NONE) {
		sysctl_register_oid(&sysctl__hw_cputhreadtype);
	}

#if defined (__i386__) || defined (__x86_64__)
	/* hw.cpufamily */
	cpufamily = cpuid_cpufamily();

	/* hw.cacheconfig */
	cacheconfig[0] = ml_cpu_cache_sharing(0);
	cacheconfig[1] = ml_cpu_cache_sharing(1);
	cacheconfig[2] = ml_cpu_cache_sharing(2);
	cacheconfig[3] = ml_cpu_cache_sharing(3);
	cacheconfig[4] = 0;

	/* hw.cachesize */
	cachesize[0] = ml_cpu_cache_size(0);
	cachesize[1] = ml_cpu_cache_size(1);
	cachesize[2] = ml_cpu_cache_size(2);
	cachesize[3] = ml_cpu_cache_size(3);
	cachesize[4] = 0;

	/* hw.packages */
	packages = roundup(ml_cpu_cache_sharing(0), cpuid_info()->thread_count)
			/ cpuid_info()->thread_count;

#elif defined(__arm__) || defined(__arm64__) /* end __i386 */

	cpufamily = cpuid_get_cpufamily();

	watchpoint_flag = arm_debug_info()->num_watchpoint_pairs;
	breakpoint_flag = arm_debug_info()->num_breakpoint_pairs;

	arm_mvfp_info_t *mvfp_info = arm_mvfp_info();
	gNeon = mvfp_info->neon;
	gNeonHpfp = mvfp_info->neon_hpfp;
	gNeonFp16 = mvfp_info->neon_fp16;

	cacheconfig[0] = ml_get_max_cpus();
	cacheconfig[1] = 1;
	cacheconfig[2] = cache_info()->c_l2size ? 1:0;
	cacheconfig[3] = 0;
	cacheconfig[4] = 0;
	cacheconfig[5] = 0;
	cacheconfig[6] = 0;

	cachesize[0] = ml_get_machine_mem();
	cachesize[1] = cache_info()->c_dsize; /* Using the DCache */
	cachesize[2] = cache_info()->c_l2size;
	cachesize[3] = 0;
	cachesize[4] = 0;

	packages = 1;
#else
#error unknown architecture
#endif /* !__i386__ && !__x86_64 && !__arm__ && !__arm64__ */

}