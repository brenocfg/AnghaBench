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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_L2C_SPAR4 ; 
 int /*<<< orphan*/  OCTEON_CN38XX ; 
 int /*<<< orphan*/  OCTEON_CN58XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int cvmx_l2c_get_hw_way_partition () ; 
 int cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 
 scalar_t__ l2_size_half () ; 

int cvmx_l2c_set_hw_way_partition(uint32_t mask)
{
	uint32_t valid_mask;

	valid_mask = 0xff;

	if (OCTEON_IS_MODEL(OCTEON_CN58XX) || OCTEON_IS_MODEL(OCTEON_CN38XX)) {
		if (l2_size_half())
			valid_mask = 0xf;
	} else if (l2_size_half())
		valid_mask = 0x3;

	mask &= valid_mask;

	/* A UMSK setting which blocks all L2C Ways is an error. */
	if (mask == valid_mask)
		return -1;
	/* Check to make sure current mask & new mask don't block all ways */
	if (((mask | cvmx_l2c_get_hw_way_partition()) & valid_mask) ==
	    valid_mask)
		return -1;

	cvmx_write_csr(CVMX_L2C_SPAR4,
		       (cvmx_read_csr(CVMX_L2C_SPAR4) & ~0xFF) | mask);
	return 0;
}