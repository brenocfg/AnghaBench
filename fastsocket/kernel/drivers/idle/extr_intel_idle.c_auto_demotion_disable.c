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
 int /*<<< orphan*/  MSR_NHM_SNB_PKG_CST_CFG_CTL ; 
 unsigned long long auto_demotion_disable_flags ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static void auto_demotion_disable(void *dummy)
{
	unsigned long long msr_bits;

	rdmsrl(MSR_NHM_SNB_PKG_CST_CFG_CTL, msr_bits);
	msr_bits &= ~auto_demotion_disable_flags;
	wrmsrl(MSR_NHM_SNB_PKG_CST_CFG_CTL, msr_bits);
}