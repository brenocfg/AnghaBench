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
struct TYPE_2__ {scalar_t__ en; } ;
union cvmx_pip_tag_incx {scalar_t__ u64; TYPE_1__ s; } ;
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_PIP_TAG_INCX (int) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void cvmx_pip_tag_mask_clear(uint64_t mask_index)
{
	uint64_t index;
	union cvmx_pip_tag_incx pip_tag_incx;
	pip_tag_incx.u64 = 0;
	pip_tag_incx.s.en = 0;
	for (index = mask_index * 16; index < (mask_index + 1) * 16; index++)
		cvmx_write_csr(CVMX_PIP_TAG_INCX(index), pip_tag_incx.u64);
}