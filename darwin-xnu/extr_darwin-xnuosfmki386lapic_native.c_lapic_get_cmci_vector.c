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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */

uint8_t
lapic_get_cmci_vector(void)
{
	uint8_t	cmci_vector = 0;
#if CONFIG_MCA
	/* CMCI, if available */
	if (mca_is_cmci_present())
		cmci_vector = LAPIC_VECTOR(CMCI);
#endif
	return cmci_vector;
}