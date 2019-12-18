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
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALL_FUNCTION_IPI ; 
 int /*<<< orphan*/  send_IPI_mask (struct cpumask const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void arch_send_call_function_ipi_mask(const struct cpumask *mask)
{
	send_IPI_mask(mask, CALL_FUNCTION_IPI, 0);
}