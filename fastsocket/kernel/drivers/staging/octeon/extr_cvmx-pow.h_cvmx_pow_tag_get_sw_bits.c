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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int CVMX_TAG_SW_BITS ; 
 int cvmx_build_mask (int) ; 

__attribute__((used)) static inline uint32_t cvmx_pow_tag_get_sw_bits(uint64_t tag)
{
	return (tag >> (32 - CVMX_TAG_SW_BITS)) &
		cvmx_build_mask(CVMX_TAG_SW_BITS);
}