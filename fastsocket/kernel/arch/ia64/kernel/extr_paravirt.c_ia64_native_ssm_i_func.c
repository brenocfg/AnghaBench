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
 int /*<<< orphan*/  IA64_PSR_I ; 
 int /*<<< orphan*/  ia64_native_ssm (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ia64_native_ssm_i_func(void)
{
	ia64_native_ssm(IA64_PSR_I);
}