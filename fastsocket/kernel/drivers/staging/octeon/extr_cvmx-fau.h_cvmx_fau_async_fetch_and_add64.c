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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  cvmx_fau_reg_64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_FAU_OP_SIZE_64 ; 
 int /*<<< orphan*/  __cvmx_fau_iobdma_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_send_single (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cvmx_fau_async_fetch_and_add64(uint64_t scraddr,
						  cvmx_fau_reg_64_t reg,
						  int64_t value)
{
	cvmx_send_single(__cvmx_fau_iobdma_data
			 (scraddr, value, 0, CVMX_FAU_OP_SIZE_64, reg));
}