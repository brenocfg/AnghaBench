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
struct TYPE_2__ {int cnt0sel; int cnt0ena; int cnt0rdclr; int cnt1sel; int cnt1ena; int cnt1rdclr; int cnt2sel; int cnt2ena; int cnt2rdclr; int cnt3sel; int cnt3ena; int cnt3rdclr; } ;
union cvmx_l2c_pfctl {int /*<<< orphan*/  u64; TYPE_1__ s; } ;
typedef  int uint32_t ;
typedef  enum cvmx_l2c_event { ____Placeholder_cvmx_l2c_event } cvmx_l2c_event ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_L2C_PFCTL ; 
 int /*<<< orphan*/  cvmx_octeon_is_pass1 () ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cvmx_l2c_config_perf(uint32_t counter, enum cvmx_l2c_event event,
			  uint32_t clear_on_read)
{
	union cvmx_l2c_pfctl pfctl;

	pfctl.u64 = cvmx_read_csr(CVMX_L2C_PFCTL);

	switch (counter) {
	case 0:
		pfctl.s.cnt0sel = event;
		pfctl.s.cnt0ena = 1;
		if (!cvmx_octeon_is_pass1())
			pfctl.s.cnt0rdclr = clear_on_read;
		break;
	case 1:
		pfctl.s.cnt1sel = event;
		pfctl.s.cnt1ena = 1;
		if (!cvmx_octeon_is_pass1())
			pfctl.s.cnt1rdclr = clear_on_read;
		break;
	case 2:
		pfctl.s.cnt2sel = event;
		pfctl.s.cnt2ena = 1;
		if (!cvmx_octeon_is_pass1())
			pfctl.s.cnt2rdclr = clear_on_read;
		break;
	case 3:
	default:
		pfctl.s.cnt3sel = event;
		pfctl.s.cnt3ena = 1;
		if (!cvmx_octeon_is_pass1())
			pfctl.s.cnt3rdclr = clear_on_read;
		break;
	}

	cvmx_write_csr(CVMX_L2C_PFCTL, pfctl.u64);
}