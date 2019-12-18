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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int menelaus_get_vtg_value (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int menelaus_set_voltage (int /*<<< orphan*/ *,unsigned int,int,int) ; 
 int /*<<< orphan*/  vmem_values ; 
 int /*<<< orphan*/  vmem_vtg ; 

int menelaus_set_vmem(unsigned int mV)
{
	int val;

	if (mV == 0)
		return menelaus_set_voltage(&vmem_vtg, 0, 0, 0);

	val = menelaus_get_vtg_value(mV, vmem_values, ARRAY_SIZE(vmem_values));
	if (val < 0)
		return -EINVAL;
	return menelaus_set_voltage(&vmem_vtg, mV, val, 0x02);
}