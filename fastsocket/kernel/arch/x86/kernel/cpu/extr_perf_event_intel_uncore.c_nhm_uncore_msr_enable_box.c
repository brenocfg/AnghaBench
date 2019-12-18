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
struct intel_uncore_box {int dummy; } ;

/* Variables and functions */
 int NHM_UNC_GLOBAL_CTL_EN_FC ; 
 int NHM_UNC_GLOBAL_CTL_EN_PC_ALL ; 
 int /*<<< orphan*/  NHM_UNC_PERF_GLOBAL_CTL ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nhm_uncore_msr_enable_box(struct intel_uncore_box *box)
{
	wrmsrl(NHM_UNC_PERF_GLOBAL_CTL, NHM_UNC_GLOBAL_CTL_EN_PC_ALL | NHM_UNC_GLOBAL_CTL_EN_FC);
}