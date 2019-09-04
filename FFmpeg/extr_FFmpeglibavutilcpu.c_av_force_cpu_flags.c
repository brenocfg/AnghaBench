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

/* Variables and functions */
 scalar_t__ ARCH_X86 ; 
 int AV_CPU_FLAG_3DNOW ; 
 int AV_CPU_FLAG_3DNOWEXT ; 
 int AV_CPU_FLAG_AVX ; 
 int AV_CPU_FLAG_AVX2 ; 
 int AV_CPU_FLAG_AVX512 ; 
 int AV_CPU_FLAG_AVXSLOW ; 
 int AV_CPU_FLAG_FMA3 ; 
 int AV_CPU_FLAG_FMA4 ; 
 int AV_CPU_FLAG_MMX ; 
 int AV_CPU_FLAG_MMXEXT ; 
 int AV_CPU_FLAG_SSE ; 
 int AV_CPU_FLAG_SSE2 ; 
 int AV_CPU_FLAG_SSE2SLOW ; 
 int AV_CPU_FLAG_SSE3 ; 
 int AV_CPU_FLAG_SSE3SLOW ; 
 int AV_CPU_FLAG_SSE4 ; 
 int AV_CPU_FLAG_SSE42 ; 
 int AV_CPU_FLAG_SSSE3 ; 
 int AV_CPU_FLAG_XOP ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  atomic_store_explicit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cpu_flags ; 
 int /*<<< orphan*/  memory_order_relaxed ; 

void av_force_cpu_flags(int arg){
    if (ARCH_X86 &&
           (arg & ( AV_CPU_FLAG_3DNOW    |
                    AV_CPU_FLAG_3DNOWEXT |
                    AV_CPU_FLAG_MMXEXT   |
                    AV_CPU_FLAG_SSE      |
                    AV_CPU_FLAG_SSE2     |
                    AV_CPU_FLAG_SSE2SLOW |
                    AV_CPU_FLAG_SSE3     |
                    AV_CPU_FLAG_SSE3SLOW |
                    AV_CPU_FLAG_SSSE3    |
                    AV_CPU_FLAG_SSE4     |
                    AV_CPU_FLAG_SSE42    |
                    AV_CPU_FLAG_AVX      |
                    AV_CPU_FLAG_AVXSLOW  |
                    AV_CPU_FLAG_XOP      |
                    AV_CPU_FLAG_FMA3     |
                    AV_CPU_FLAG_FMA4     |
                    AV_CPU_FLAG_AVX2     |
                    AV_CPU_FLAG_AVX512   ))
        && !(arg & AV_CPU_FLAG_MMX)) {
        av_log(NULL, AV_LOG_WARNING, "MMX implied by specified flags\n");
        arg |= AV_CPU_FLAG_MMX;
    }

    atomic_store_explicit(&cpu_flags, arg, memory_order_relaxed);
}