#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int cache_line_size; } ;
typedef  TYPE_1__ ml_cpu_info_t ;

/* Variables and functions */
 scalar_t__ _COMM_PAGE_CPU_CAPABILITIES ; 
 scalar_t__ _COMM_PAGE_RW_OFFSET ; 
 int _cpu_capabilities ; 
 int commpage_cpus () ; 
 int kCache128 ; 
 int kCache32 ; 
 int kCache64 ; 
 int kFastThreadLocalStorage ; 
 int kNumCPUsShift ; 
 int kUP ; 
 int /*<<< orphan*/  ml_cpu_get_info (TYPE_1__*) ; 

__attribute__((used)) static void
commpage_init_cpu_capabilities( void )
{
	uint32_t bits;
	int cpus;
	ml_cpu_info_t cpu_info;

	bits = 0;
	ml_cpu_get_info(&cpu_info);

	switch (cpu_info.cache_line_size) {
		case 128:
			bits |= kCache128;
			break;
		case 64:
			bits |= kCache64;
			break;
		case 32:
			bits |= kCache32;
			break;
		default:
			break;
	}
	cpus = commpage_cpus();

	if (cpus == 1)
		bits |= kUP;

	bits |= (cpus << kNumCPUsShift);

	bits |= kFastThreadLocalStorage;        // TPIDRURO for TLS

#if	__ARM_VFP__
	bits |= kHasVfp;
	arm_mvfp_info_t *mvfp_info = arm_mvfp_info();
	if (mvfp_info->neon)
		bits |= kHasNeon;
	if (mvfp_info->neon_hpfp)
		bits |= kHasNeonHPFP;
	if (mvfp_info->neon_fp16)
		bits |= kHasNeonFP16;
#endif
#if defined(__arm64__)
	bits |= kHasFMA;
#endif
#if	__ARM_ENABLE_WFE_
#ifdef __arm64__
	if (arm64_wfe_allowed()) {
		bits |= kHasEvent;
	}
#else
	bits |= kHasEvent;
#endif
#endif
#if __ARM_V8_CRYPTO_EXTENSIONS__ 
	bits |= kHasARMv8Crypto;
#endif
#ifdef __arm64__
	uint64_t isar0 = __builtin_arm_rsr64("ID_AA64ISAR0_EL1");
	if ((isar0 & ID_AA64ISAR0_EL1_ATOMIC_MASK) == ID_AA64ISAR0_EL1_ATOMIC_8_1) {
		bits |= kHasARMv81Atomics;
		gARMv81Atomics = 1;
	}
	if ((isar0 & ID_AA64ISAR0_EL1_CRC32_MASK) == ID_AA64ISAR0_EL1_CRC32_EN) {
		bits |= kHasARMv8Crc32;
		gARMv8Crc32 = 1;
	}
#endif
	_cpu_capabilities = bits;

	*((uint32_t *)(_COMM_PAGE_CPU_CAPABILITIES+_COMM_PAGE_RW_OFFSET)) = _cpu_capabilities;
}