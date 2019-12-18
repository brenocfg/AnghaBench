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
typedef  int /*<<< orphan*/  i386_intr_func_t ;

/* Variables and functions */
 int /*<<< orphan*/  LAPIC_VECTOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERFCNT ; 
 int /*<<< orphan*/  lapic_set_intr_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void	lapic_set_pmi_func(i386_intr_func_t func) {
	lapic_set_intr_func(LAPIC_VECTOR(PERFCNT), func);
}