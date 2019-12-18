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
struct cas {int dummy; } ;

/* Variables and functions */
 int N_RX_COMP_RINGS ; 
 int /*<<< orphan*/  cas_enable_irq (struct cas*,int) ; 

__attribute__((used)) static inline void cas_unmask_intr(struct cas *cp)
{
	int i;

	for (i = 0; i < N_RX_COMP_RINGS; i++)
		cas_enable_irq(cp, i);
}