#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int intel; int cmov; int mmx; int sse; int sse2; int sse3; int ssse3; int sse41; int sse42; int avx; int fma; int avx2; } ;
struct TYPE_5__ {int use_asm; TYPE_1__ ia32; } ;
typedef  int FLAC__uint32 ;
typedef  int FLAC__bool ;
typedef  TYPE_2__ FLAC__CPUInfo ;

/* Variables and functions */
 scalar_t__ FLAC__AVX_SUPPORTED ; 
 int FLAC__CPUINFO_IA32_CPUID_AVX ; 
 int FLAC__CPUINFO_IA32_CPUID_AVX2 ; 
 int FLAC__CPUINFO_IA32_CPUID_CMOV ; 
 int FLAC__CPUINFO_IA32_CPUID_FMA ; 
 int FLAC__CPUINFO_IA32_CPUID_MMX ; 
 int FLAC__CPUINFO_IA32_CPUID_OSXSAVE ; 
 int FLAC__CPUINFO_IA32_CPUID_SSE ; 
 int FLAC__CPUINFO_IA32_CPUID_SSE2 ; 
 int FLAC__CPUINFO_IA32_CPUID_SSE3 ; 
 int FLAC__CPUINFO_IA32_CPUID_SSE41 ; 
 int FLAC__CPUINFO_IA32_CPUID_SSE42 ; 
 int FLAC__CPUINFO_IA32_CPUID_SSSE3 ; 
 scalar_t__ FLAC__HAS_X86INTRIN ; 
 int /*<<< orphan*/  FLAC__cpu_have_cpuid_asm_ia32 () ; 
 int /*<<< orphan*/  FLAC__cpu_info_asm_ia32 (int*,int*) ; 
 int /*<<< orphan*/  FLAC__cpu_info_x86 (int,int*,int*,int*,int*) ; 
 int cpu_xgetbv_x86 () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
ia32_cpu_info (FLAC__CPUInfo *info)
{
#if !defined FLAC__CPU_IA32
	(void) info;
#else
	FLAC__bool ia32_osxsave = false;
	FLAC__uint32 flags_eax, flags_ebx, flags_ecx, flags_edx;

#if !defined FLAC__NO_ASM && (defined FLAC__HAS_NASM || FLAC__HAS_X86INTRIN)
	info->use_asm = true; /* we assume a minimum of 80386 with FLAC__CPU_IA32 */
#if defined FLAC__HAS_NASM
	if(!FLAC__cpu_have_cpuid_asm_ia32())
		return;
#endif
	/* http://www.sandpile.org/x86/cpuid.htm */
	if (FLAC__HAS_X86INTRIN) {
		FLAC__cpu_info_x86(0, &flags_eax, &flags_ebx, &flags_ecx, &flags_edx);
		info->ia32.intel = (flags_ebx == 0x756E6547 && flags_edx == 0x49656E69 && flags_ecx == 0x6C65746E) ? true : false; /* GenuineIntel */
		FLAC__cpu_info_x86(1, &flags_eax, &flags_ebx, &flags_ecx, &flags_edx);
	}
	else {
		FLAC__cpu_info_asm_ia32(&flags_edx, &flags_ecx);
	}

	info->ia32.cmov  = (flags_edx & FLAC__CPUINFO_IA32_CPUID_CMOV ) ? true : false;
	info->ia32.mmx   = (flags_edx & FLAC__CPUINFO_IA32_CPUID_MMX  ) ? true : false;
	info->ia32.sse   = (flags_edx & FLAC__CPUINFO_IA32_CPUID_SSE  ) ? true : false;
	info->ia32.sse2  = (flags_edx & FLAC__CPUINFO_IA32_CPUID_SSE2 ) ? true : false;
	info->ia32.sse3  = (flags_ecx & FLAC__CPUINFO_IA32_CPUID_SSE3 ) ? true : false;
	info->ia32.ssse3 = (flags_ecx & FLAC__CPUINFO_IA32_CPUID_SSSE3) ? true : false;
	info->ia32.sse41 = (flags_ecx & FLAC__CPUINFO_IA32_CPUID_SSE41) ? true : false;
	info->ia32.sse42 = (flags_ecx & FLAC__CPUINFO_IA32_CPUID_SSE42) ? true : false;

	if (FLAC__HAS_X86INTRIN && FLAC__AVX_SUPPORTED) {
		ia32_osxsave = (flags_ecx & FLAC__CPUINFO_IA32_CPUID_OSXSAVE) ? true : false;
		info->ia32.avx   = (flags_ecx & FLAC__CPUINFO_IA32_CPUID_AVX    ) ? true : false;
		info->ia32.fma   = (flags_ecx & FLAC__CPUINFO_IA32_CPUID_FMA    ) ? true : false;
		FLAC__cpu_info_x86(7, &flags_eax, &flags_ebx, &flags_ecx, &flags_edx);
		info->ia32.avx2  = (flags_ebx & FLAC__CPUINFO_IA32_CPUID_AVX2   ) ? true : false;
	}

#if 0
	fprintf(stderr, "CPU info (IA-32):\n");
	fprintf(stderr, "  CMOV ....... %c\n", info->ia32.cmov    ? 'Y' : 'n');
	fprintf(stderr, "  MMX ........ %c\n", info->ia32.mmx     ? 'Y' : 'n');
	fprintf(stderr, "  SSE ........ %c\n", info->ia32.sse     ? 'Y' : 'n');
	fprintf(stderr, "  SSE2 ....... %c\n", info->ia32.sse2    ? 'Y' : 'n');
	fprintf(stderr, "  SSE3 ....... %c\n", info->ia32.sse3    ? 'Y' : 'n');
	fprintf(stderr, "  SSSE3 ...... %c\n", info->ia32.ssse3   ? 'Y' : 'n');
	fprintf(stderr, "  SSE41 ...... %c\n", info->ia32.sse41   ? 'Y' : 'n');
	fprintf(stderr, "  SSE42 ...... %c\n", info->ia32.sse42   ? 'Y' : 'n');

	if (FLAC__HAS_X86INTRIN && FLAC__AVX_SUPPORTED) {
		fprintf(stderr, "  AVX ........ %c\n", info->ia32.avx     ? 'Y' : 'n');
		fprintf(stderr, "  FMA ........ %c\n", info->ia32.fma     ? 'Y' : 'n');
		fprintf(stderr, "  AVX2 ....... %c\n", info->ia32.avx2    ? 'Y' : 'n');
	}
#endif

	/*
	 * now have to check for OS support of AVX instructions
	 */
	if (!FLAC__HAS_X86INTRIN || !info->ia32.avx || !ia32_osxsave || (cpu_xgetbv_x86() & 0x6) != 0x6) {
		/* no OS AVX support */
		info->ia32.avx     = false;
		info->ia32.avx2    = false;
		info->ia32.fma     = false;
	}

#if 0
	if (FLAC__HAS_X86INTRIN && FLAC__AVX_SUPPORTED)
      fprintf(stderr, "  AVX OS sup . %c\n", info->ia32.avx ? 'Y' : 'n');
#endif
#else
	info->use_asm = false;
#endif
#endif
}