#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int vector_unit; scalar_t__ l1_icache_size; scalar_t__ l1_dcache_size; int l2_settings; scalar_t__ l2_cache_size; int l3_settings; scalar_t__ l3_cache_size; int /*<<< orphan*/  cache_line_size; } ;
typedef  TYPE_1__ ml_cpu_info_t ;
struct TYPE_6__ {scalar_t__* cache_size; int /*<<< orphan*/  cache_linesize; } ;
typedef  TYPE_2__ i386_cpu_info_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int CPUID_FEATURE_MMX ; 
 int CPUID_FEATURE_SSE ; 
 int CPUID_FEATURE_SSE2 ; 
 int CPUID_FEATURE_SSE3 ; 
 int CPUID_FEATURE_SSE4_1 ; 
 int CPUID_FEATURE_SSE4_2 ; 
 int CPUID_FEATURE_SSSE3 ; 
 int CR4_OSXMM ; 
 size_t L1D ; 
 size_t L1I ; 
 size_t L2U ; 
 size_t L3U ; 
 int cpuid_features () ; 
 TYPE_2__* cpuid_info () ; 
 int get_cr4 () ; 
 scalar_t__ ml_fpu_avx_enabled () ; 

void
ml_cpu_get_info(ml_cpu_info_t *cpu_infop)
{
	boolean_t	os_supports_sse;
	i386_cpu_info_t *cpuid_infop;

	if (cpu_infop == NULL)
		return;
 
	/*
	 * Are we supporting MMX/SSE/SSE2/SSE3?
	 * As distinct from whether the cpu has these capabilities.
	 */
	os_supports_sse = !!(get_cr4() & CR4_OSXMM);

	if (ml_fpu_avx_enabled())
		cpu_infop->vector_unit = 9;
	else if ((cpuid_features() & CPUID_FEATURE_SSE4_2) && os_supports_sse)
		cpu_infop->vector_unit = 8;
	else if ((cpuid_features() & CPUID_FEATURE_SSE4_1) && os_supports_sse)
		cpu_infop->vector_unit = 7;
	else if ((cpuid_features() & CPUID_FEATURE_SSSE3) && os_supports_sse)
		cpu_infop->vector_unit = 6;
	else if ((cpuid_features() & CPUID_FEATURE_SSE3) && os_supports_sse)
		cpu_infop->vector_unit = 5;
	else if ((cpuid_features() & CPUID_FEATURE_SSE2) && os_supports_sse)
		cpu_infop->vector_unit = 4;
	else if ((cpuid_features() & CPUID_FEATURE_SSE) && os_supports_sse)
		cpu_infop->vector_unit = 3;
	else if (cpuid_features() & CPUID_FEATURE_MMX)
		cpu_infop->vector_unit = 2;
	else
		cpu_infop->vector_unit = 0;

	cpuid_infop  = cpuid_info();

	cpu_infop->cache_line_size = cpuid_infop->cache_linesize; 

	cpu_infop->l1_icache_size = cpuid_infop->cache_size[L1I];
	cpu_infop->l1_dcache_size = cpuid_infop->cache_size[L1D];
  
        if (cpuid_infop->cache_size[L2U] > 0) {
            cpu_infop->l2_settings = 1;
            cpu_infop->l2_cache_size = cpuid_infop->cache_size[L2U];
        } else {
            cpu_infop->l2_settings = 0;
            cpu_infop->l2_cache_size = 0xFFFFFFFF;
        }

        if (cpuid_infop->cache_size[L3U] > 0) {
            cpu_infop->l3_settings = 1;
            cpu_infop->l3_cache_size = cpuid_infop->cache_size[L3U];
        } else {
            cpu_infop->l3_settings = 0;
            cpu_infop->l3_cache_size = 0xFFFFFFFF;
        }
}