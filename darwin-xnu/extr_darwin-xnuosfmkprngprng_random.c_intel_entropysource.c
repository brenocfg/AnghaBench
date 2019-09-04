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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int CPUID_FEATURE_RDRAND ; 
 int CPUID_LEAF7_FEATURE_RDSEED ; 
 int /*<<< orphan*/  assert (int) ; 
 int cpuid_features () ; 
 int cpuid_leaf7_features () ; 
 size_t rdrand_seed (void*,size_t) ; 
 size_t rdseed_seed (void*,size_t) ; 

__attribute__((used)) static void
intel_entropysource(void * buf, size_t * nbytes)
{
	size_t nwords;

	/* only handle complete words */
	assert(*nbytes % sizeof(uint64_t) == 0);

	nwords = (*nbytes) / sizeof(uint64_t);
	if (cpuid_leaf7_features() & CPUID_LEAF7_FEATURE_RDSEED) {
		nwords  = rdseed_seed(buf, nwords);
		*nbytes = nwords * sizeof(uint64_t);
	} else if (cpuid_features() & CPUID_FEATURE_RDRAND) {
		nwords  = rdrand_seed(buf, nwords);
		*nbytes = nwords * sizeof(uint64_t);
	} else {
		*nbytes = 0;
	}
}