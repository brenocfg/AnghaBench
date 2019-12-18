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
struct TYPE_4__ {int intel; int sse3; int ssse3; int sse41; int sse42; int avx; int fma; int avx2; } ;
struct TYPE_5__ {int use_asm; TYPE_1__ x86; } ;
typedef  int FLAC__uint32 ;
typedef  int FLAC__bool ;
typedef  TYPE_2__ FLAC__CPUInfo ;

/* Variables and functions */
 scalar_t__ FLAC__AVX_SUPPORTED ; 
 int FLAC__CPUINFO_IA32_CPUID_AVX ; 
 int FLAC__CPUINFO_IA32_CPUID_AVX2 ; 
 int FLAC__CPUINFO_IA32_CPUID_FMA ; 
 int FLAC__CPUINFO_IA32_CPUID_OSXSAVE ; 
 int FLAC__CPUINFO_IA32_CPUID_SSE3 ; 
 int FLAC__CPUINFO_IA32_CPUID_SSE41 ; 
 int FLAC__CPUINFO_IA32_CPUID_SSE42 ; 
 int FLAC__CPUINFO_IA32_CPUID_SSSE3 ; 
 int /*<<< orphan*/  FLAC__cpu_info_x86 (int,int*,int*,int*,int*) ; 
 int cpu_xgetbv_x86 () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
x86_64_cpu_info (FLAC__CPUInfo *info)
{
#if !defined FLAC__NO_ASM && FLAC__HAS_X86INTRIN
	FLAC__bool x86_osxsave = false;
	FLAC__uint32 flags_eax, flags_ebx, flags_ecx, flags_edx;

	info->use_asm = true;

	/* http://www.sandpile.org/x86/cpuid.htm */
	FLAC__cpu_info_x86(0, &flags_eax, &flags_ebx, &flags_ecx, &flags_edx);
	info->x86.intel = (flags_ebx == 0x756E6547 && flags_edx == 0x49656E69 && flags_ecx == 0x6C65746E) ? true : false; /* GenuineIntel */
	FLAC__cpu_info_x86(1, &flags_eax, &flags_ebx, &flags_ecx, &flags_edx);
	info->x86.sse3  = (flags_ecx & FLAC__CPUINFO_IA32_CPUID_SSE3 ) ? true : false;
	info->x86.ssse3 = (flags_ecx & FLAC__CPUINFO_IA32_CPUID_SSSE3) ? true : false;
	info->x86.sse41 = (flags_ecx & FLAC__CPUINFO_IA32_CPUID_SSE41) ? true : false;
	info->x86.sse42 = (flags_ecx & FLAC__CPUINFO_IA32_CPUID_SSE42) ? true : false;

	if (FLAC__AVX_SUPPORTED) {
		x86_osxsave = (flags_ecx & FLAC__CPUINFO_IA32_CPUID_OSXSAVE) ? true : false;
		info->x86.avx   = (flags_ecx & FLAC__CPUINFO_IA32_CPUID_AVX    ) ? true : false;
		info->x86.fma   = (flags_ecx & FLAC__CPUINFO_IA32_CPUID_FMA    ) ? true : false;
		FLAC__cpu_info_x86(7, &flags_eax, &flags_ebx, &flags_ecx, &flags_edx);
		info->x86.avx2  = (flags_ebx & FLAC__CPUINFO_IA32_CPUID_AVX2   ) ? true : false;
	}

	fprintf(stderr, "CPU info (x86-64):\n");
	fprintf(stderr, "  SSE3 ....... %c\n", info->x86.sse3  ? 'Y' : 'n');
	fprintf(stderr, "  SSSE3 ...... %c\n", info->x86.ssse3 ? 'Y' : 'n');
	fprintf(stderr, "  SSE41 ...... %c\n", info->x86.sse41 ? 'Y' : 'n');
	fprintf(stderr, "  SSE42 ...... %c\n", info->x86.sse42 ? 'Y' : 'n');

	if (FLAC__AVX_SUPPORTED) {
		fprintf(stderr, "  AVX ........ %c\n", info->x86.avx   ? 'Y' : 'n');
		fprintf(stderr, "  FMA ........ %c\n", info->x86.fma   ? 'Y' : 'n');
		fprintf(stderr, "  AVX2 ....... %c\n", info->x86.avx2  ? 'Y' : 'n');
	}

	/*
	 * now have to check for OS support of AVX instructions
	 */
	if (!info->x86.avx || !x86_osxsave || (cpu_xgetbv_x86() & 0x6) != 0x6) {
		/* no OS AVX support */
		info->x86.avx     = false;
		info->x86.avx2    = false;
		info->x86.fma     = false;
	}

	if (FLAC__AVX_SUPPORTED) {
		fprintf(stderr, "  AVX OS sup . %c\n", info->x86.avx ? 'Y' : 'n');
	}
#else
	/* Silence compiler warnings. */
	(void) info;
#if defined FLAC__CPU_IA32 || defined FLAC__CPU_X86_64
	if (0) cpu_xgetbv_x86 ();
#endif
#endif
}