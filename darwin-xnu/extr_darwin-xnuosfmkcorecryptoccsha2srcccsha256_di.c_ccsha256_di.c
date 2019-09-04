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
struct ccdigest_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIPSPOST_TRACE_EVENT ; 
 struct ccdigest_info const ccsha256_ltc_di ; 

const struct ccdigest_info *ccsha256_di(void)
{
    FIPSPOST_TRACE_EVENT;

#if  CCSHA2_VNG_INTEL
#if defined (__x86_64__)
    if (CC_HAS_AVX512_AND_IN_KERNEL())
        return &ccsha256_vng_intel_SupplementalSSE3_di;
    else
    return ( (CC_HAS_AVX2() ? &ccsha256_vng_intel_AVX2_di :
    		( (CC_HAS_AVX1() ? &ccsha256_vng_intel_AVX1_di :
			&ccsha256_vng_intel_SupplementalSSE3_di ) ) ) ) ;
#else
    return &ccsha256_vng_intel_SupplementalSSE3_di;
#endif
#elif  CCSHA2_VNG_ARMV7NEON
    return &ccsha256_vng_armv7neon_di;
#elif CCSHA256_ARMV6M_ASM
    return &ccsha256_v6m_di;
#else
    return &ccsha256_ltc_di;
#endif
}