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

/* Variables and functions */
 int CVMX_FPA_PACKET_POOL_SIZE ; 
 int /*<<< orphan*/  CVMX_FPA_WQE_POOL ; 
 int /*<<< orphan*/  CVMX_HELPER_ENABLE_BACK_PRESSURE ; 
 int CVMX_HELPER_FIRST_MBUFF_SKIP ; 
 int CVMX_HELPER_NOT_FIRST_MBUFF_SKIP ; 
 int /*<<< orphan*/  CVMX_IPD_OPC_MODE_STT ; 
 int /*<<< orphan*/  cvmx_ipd_config (int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __cvmx_helper_global_setup_ipd(void)
{
	/* Setup the global packet input options */
	cvmx_ipd_config(CVMX_FPA_PACKET_POOL_SIZE / 8,
			CVMX_HELPER_FIRST_MBUFF_SKIP / 8,
			CVMX_HELPER_NOT_FIRST_MBUFF_SKIP / 8,
			/* The +8 is to account for the next ptr */
			(CVMX_HELPER_FIRST_MBUFF_SKIP + 8) / 128,
			/* The +8 is to account for the next ptr */
			(CVMX_HELPER_NOT_FIRST_MBUFF_SKIP + 8) / 128,
			CVMX_FPA_WQE_POOL,
			CVMX_IPD_OPC_MODE_STT,
			CVMX_HELPER_ENABLE_BACK_PRESSURE);
	return 0;
}