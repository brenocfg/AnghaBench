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
 int CBS_IDLE ; 
 int /*<<< orphan*/  GRU_NUM_KERNEL_DSR_BYTES ; 
 int /*<<< orphan*/  IMA ; 
 int MQE_BUG_NO_RESOURCES ; 
 int /*<<< orphan*/  STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gru_free_cpu_resources (void*,void*) ; 
 scalar_t__ gru_get_cpu_resources (int /*<<< orphan*/ ,void**,void**) ; 
 int /*<<< orphan*/  gru_get_tri (void*) ; 
 int /*<<< orphan*/  gru_vload_phys (void*,unsigned long,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int gru_wait (void*) ; 
 int /*<<< orphan*/  read_gpa ; 

int gru_read_gpa(unsigned long *value, unsigned long gpa)
{
	void *cb;
	void *dsr;
	int ret, iaa;

	STAT(read_gpa);
	if (gru_get_cpu_resources(GRU_NUM_KERNEL_DSR_BYTES, &cb, &dsr))
		return MQE_BUG_NO_RESOURCES;
	iaa = gpa >> 62;
	gru_vload_phys(cb, gpa, gru_get_tri(dsr), iaa, IMA);
	ret = gru_wait(cb);
	if (ret == CBS_IDLE)
		*value = *(unsigned long *)dsr;
	gru_free_cpu_resources(cb, dsr);
	return ret;
}