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
struct TYPE_2__ {int /*<<< orphan*/  grp_msk; } ;
union cvmx_pow_pp_grp_mskx {int /*<<< orphan*/  u64; TYPE_1__ s; } ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_POW_PP_GRP_MSKX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cvmx_pow_set_group_mask(uint64_t core_num, uint64_t mask)
{
	union cvmx_pow_pp_grp_mskx grp_msk;

	grp_msk.u64 = cvmx_read_csr(CVMX_POW_PP_GRP_MSKX(core_num));
	grp_msk.s.grp_msk = mask;
	cvmx_write_csr(CVMX_POW_PP_GRP_MSKX(core_num), grp_msk.u64);
}