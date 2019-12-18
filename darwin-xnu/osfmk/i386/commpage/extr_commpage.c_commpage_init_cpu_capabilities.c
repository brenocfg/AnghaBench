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
typedef  int uint64_t ;
struct TYPE_3__ {int vector_unit; int cache_line_size; } ;
typedef  TYPE_1__ ml_cpu_info_t ;

/* Variables and functions */
 int CPUID_FEATURE_AES ; 
 int CPUID_FEATURE_F16C ; 
 int CPUID_FEATURE_FMA ; 
 int CPUID_FEATURE_RDRAND ; 
 int CPUID_LEAF7_FEATURE_ADX ; 
 int CPUID_LEAF7_FEATURE_AVX2 ; 
 int CPUID_LEAF7_FEATURE_AVX512BW ; 
 int CPUID_LEAF7_FEATURE_AVX512CD ; 
 int CPUID_LEAF7_FEATURE_AVX512DQ ; 
 int CPUID_LEAF7_FEATURE_AVX512F ; 
 int CPUID_LEAF7_FEATURE_AVX512IFMA ; 
 int CPUID_LEAF7_FEATURE_AVX512VBMI ; 
 int CPUID_LEAF7_FEATURE_AVX512VL ; 
 int CPUID_LEAF7_FEATURE_BMI1 ; 
 int CPUID_LEAF7_FEATURE_BMI2 ; 
 int CPUID_LEAF7_FEATURE_ERMS ; 
 int CPUID_LEAF7_FEATURE_HLE ; 
 int CPUID_LEAF7_FEATURE_MPX ; 
 int CPUID_LEAF7_FEATURE_RDSEED ; 
 int CPUID_LEAF7_FEATURE_RTM ; 
 int CPUID_LEAF7_FEATURE_SGX ; 
 int /*<<< orphan*/  MSR_IA32_MISC_ENABLE ; 
 scalar_t__ SLOW_TSC_THRESHOLD ; 
 int _cpu_capabilities ; 
 int commpage_cpus () ; 
 int cpu_mode_is64bit () ; 
 int cpuid_features () ; 
 int cpuid_leaf7_features () ; 
 int /*<<< orphan*/  k64Bit ; 
 int kCache128 ; 
 int kCache32 ; 
 int kCache64 ; 
 int kFastThreadLocalStorage ; 
 int /*<<< orphan*/  kHasADX ; 
 int /*<<< orphan*/  kHasAES ; 
 int kHasAVX1_0 ; 
 int /*<<< orphan*/  kHasAVX2_0 ; 
 int /*<<< orphan*/  kHasAVX512BW ; 
 int /*<<< orphan*/  kHasAVX512CD ; 
 int /*<<< orphan*/  kHasAVX512DQ ; 
 int /*<<< orphan*/  kHasAVX512F ; 
 int /*<<< orphan*/  kHasAVX512IFMA ; 
 int /*<<< orphan*/  kHasAVX512VBMI ; 
 int /*<<< orphan*/  kHasAVX512VL ; 
 int /*<<< orphan*/  kHasBMI1 ; 
 int /*<<< orphan*/  kHasBMI2 ; 
 int /*<<< orphan*/  kHasENFSTRG ; 
 int /*<<< orphan*/  kHasF16C ; 
 int /*<<< orphan*/  kHasFMA ; 
 int /*<<< orphan*/  kHasHLE ; 
 int kHasMMX ; 
 int /*<<< orphan*/  kHasMPX ; 
 int /*<<< orphan*/  kHasRDRAND ; 
 int /*<<< orphan*/  kHasRDSEED ; 
 int /*<<< orphan*/  kHasRTM ; 
 int /*<<< orphan*/  kHasSGX ; 
 int kHasSSE ; 
 int kHasSSE2 ; 
 int kHasSSE3 ; 
 int kHasSSE4_1 ; 
 int kHasSSE4_2 ; 
 int kHasSupplementalSSE3 ; 
 int kNumCPUsShift ; 
 int /*<<< orphan*/  kSlow ; 
 int /*<<< orphan*/  kUP ; 
 int /*<<< orphan*/  ml_cpu_get_info (TYPE_1__*) ; 
 scalar_t__ ml_fpu_avx512_enabled () ; 
 int rdmsr64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setif (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tscFreq ; 

__attribute__((used)) static void
commpage_init_cpu_capabilities( void )
{
	uint64_t bits;
	int cpus;
	ml_cpu_info_t cpu_info;

	bits = 0;
	ml_cpu_get_info(&cpu_info);
	
	switch (cpu_info.vector_unit) {
		case 9:
			bits |= kHasAVX1_0;
			/* fall thru */
		case 8:
			bits |= kHasSSE4_2;
			/* fall thru */
		case 7:
			bits |= kHasSSE4_1;
			/* fall thru */
		case 6:
			bits |= kHasSupplementalSSE3;
			/* fall thru */
		case 5:
			bits |= kHasSSE3;
			/* fall thru */
		case 4:
			bits |= kHasSSE2;
			/* fall thru */
		case 3:
			bits |= kHasSSE;
			/* fall thru */
		case 2:
			bits |= kHasMMX;
		default:
			break;
	}
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
	cpus = commpage_cpus();			// how many CPUs do we have

	bits |= (cpus << kNumCPUsShift);

	bits |= kFastThreadLocalStorage;	// we use %gs for TLS

#define setif(_bits, _bit, _condition) \
	if (_condition) _bits |= _bit

	setif(bits, kUP,         cpus == 1);
	setif(bits, k64Bit,      cpu_mode_is64bit());
	setif(bits, kSlow,       tscFreq <= SLOW_TSC_THRESHOLD);

	setif(bits, kHasAES,     cpuid_features() &
					CPUID_FEATURE_AES);
	setif(bits, kHasF16C,    cpuid_features() &
					CPUID_FEATURE_F16C);
	setif(bits, kHasRDRAND,  cpuid_features() &
					CPUID_FEATURE_RDRAND);
	setif(bits, kHasFMA,     cpuid_features() &
					CPUID_FEATURE_FMA);

	setif(bits, kHasBMI1,    cpuid_leaf7_features() &
					CPUID_LEAF7_FEATURE_BMI1);
	setif(bits, kHasBMI2,    cpuid_leaf7_features() &
					CPUID_LEAF7_FEATURE_BMI2);
	setif(bits, kHasRTM,     cpuid_leaf7_features() &
					CPUID_LEAF7_FEATURE_RTM);
	setif(bits, kHasHLE,     cpuid_leaf7_features() &
					CPUID_LEAF7_FEATURE_HLE);
	setif(bits, kHasAVX2_0,  cpuid_leaf7_features() &
					CPUID_LEAF7_FEATURE_AVX2);
	setif(bits, kHasRDSEED,  cpuid_leaf7_features() &
					CPUID_LEAF7_FEATURE_RDSEED);
	setif(bits, kHasADX,     cpuid_leaf7_features() &
					CPUID_LEAF7_FEATURE_ADX);
	
#if 0	/* The kernel doesn't support MPX or SGX */
	setif(bits, kHasMPX,     cpuid_leaf7_features() &
					CPUID_LEAF7_FEATURE_MPX);
	setif(bits, kHasSGX,     cpuid_leaf7_features() &
					CPUID_LEAF7_FEATURE_SGX);
#endif

#if !defined(RC_HIDE_XNU_J137)
	if (ml_fpu_avx512_enabled()) {
		setif(bits, kHasAVX512F,    cpuid_leaf7_features() &
					CPUID_LEAF7_FEATURE_AVX512F);
		setif(bits, kHasAVX512CD,   cpuid_leaf7_features() &
					CPUID_LEAF7_FEATURE_AVX512CD);
		setif(bits, kHasAVX512DQ,   cpuid_leaf7_features() &
					CPUID_LEAF7_FEATURE_AVX512DQ);
		setif(bits, kHasAVX512BW,   cpuid_leaf7_features() &
					CPUID_LEAF7_FEATURE_AVX512BW);
		setif(bits, kHasAVX512VL,   cpuid_leaf7_features() &
					CPUID_LEAF7_FEATURE_AVX512VL);
		setif(bits, kHasAVX512IFMA, cpuid_leaf7_features() &
					CPUID_LEAF7_FEATURE_AVX512IFMA);
		setif(bits, kHasAVX512VBMI, cpuid_leaf7_features() &
					CPUID_LEAF7_FEATURE_AVX512VBMI);
	}

#endif /* not RC_HIDE_XNU_J137 */
	uint64_t misc_enable = rdmsr64(MSR_IA32_MISC_ENABLE);
	setif(bits, kHasENFSTRG, (misc_enable & 1ULL) &&
				 (cpuid_leaf7_features() &
					CPUID_LEAF7_FEATURE_ERMS));
	
	_cpu_capabilities = bits;		// set kernel version for use by drivers etc
}