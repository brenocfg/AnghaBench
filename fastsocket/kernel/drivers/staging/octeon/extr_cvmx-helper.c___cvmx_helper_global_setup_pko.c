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
struct TYPE_2__ {int tout_val; scalar_t__ tout_enb; } ;
union cvmx_iob_fau_timeout {scalar_t__ u64; TYPE_1__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_IOB_FAU_TIMEOUT ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int __cvmx_helper_global_setup_pko(void)
{
	/*
	 * Disable tagwait FAU timeout. This needs to be done before
	 * anyone might start packet output using tags.
	 */
	union cvmx_iob_fau_timeout fau_to;
	fau_to.u64 = 0;
	fau_to.s.tout_val = 0xfff;
	fau_to.s.tout_enb = 0;
	cvmx_write_csr(CVMX_IOB_FAU_TIMEOUT, fau_to.u64);
	return 0;
}