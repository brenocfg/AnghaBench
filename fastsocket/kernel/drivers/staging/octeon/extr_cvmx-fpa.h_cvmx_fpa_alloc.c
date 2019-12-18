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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_ADDR_DID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_FULL_DID (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  CVMX_OCT_DID_FPA ; 
 void* cvmx_phys_to_ptr (scalar_t__) ; 
 scalar_t__ cvmx_read_csr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void *cvmx_fpa_alloc(uint64_t pool)
{
	uint64_t address =
	    cvmx_read_csr(CVMX_ADDR_DID(CVMX_FULL_DID(CVMX_OCT_DID_FPA, pool)));
	if (address)
		return cvmx_phys_to_ptr(address);
	else
		return NULL;
}