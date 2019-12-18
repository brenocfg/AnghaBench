#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ idxalias; } ;
union cvmx_l2c_cfg {TYPE_1__ s; int /*<<< orphan*/  u64; } ;
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int CVMX_L2C_ALIAS_MASK ; 
 int /*<<< orphan*/  CVMX_L2C_CFG ; 
 int CVMX_L2C_IDX_ADDR_SHIFT ; 
 int CVMX_L2C_IDX_MASK ; 
 int CVMX_L2C_TAG_ADDR_ALIAS_SHIFT ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 

uint32_t cvmx_l2c_address_to_index(uint64_t addr)
{
	uint64_t idx = addr >> CVMX_L2C_IDX_ADDR_SHIFT;
	union cvmx_l2c_cfg l2c_cfg;
	l2c_cfg.u64 = cvmx_read_csr(CVMX_L2C_CFG);

	if (l2c_cfg.s.idxalias) {
		idx ^=
		    ((addr & CVMX_L2C_ALIAS_MASK) >>
		     CVMX_L2C_TAG_ADDR_ALIAS_SHIFT);
	}
	idx &= CVMX_L2C_IDX_MASK;
	return idx;
}