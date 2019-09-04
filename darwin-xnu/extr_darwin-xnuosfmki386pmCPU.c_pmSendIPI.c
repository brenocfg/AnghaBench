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
 int /*<<< orphan*/  LAPIC_PM_INTERRUPT ; 
 int /*<<< orphan*/  lapic_send_ipi (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pmSendIPI(int cpu)
{
    lapic_send_ipi(cpu, LAPIC_PM_INTERRUPT);
}