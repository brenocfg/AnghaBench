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
 int /*<<< orphan*/  GRU_NUM_KERNEL_DSR_BYTES ; 
 int /*<<< orphan*/  GRU_NUM_KERNEL_DSR_CL ; 
 int /*<<< orphan*/  IMA ; 
 int MQE_BUG_NO_RESOURCES ; 
 int /*<<< orphan*/  STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XTYPE_B ; 
 int /*<<< orphan*/  copy_gpa ; 
 int /*<<< orphan*/  gru_bcopy (void*,unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gru_free_cpu_resources (void*,void*) ; 
 scalar_t__ gru_get_cpu_resources (int /*<<< orphan*/ ,void**,void**) ; 
 int /*<<< orphan*/  gru_get_tri (void*) ; 
 int gru_wait (void*) ; 

int gru_copy_gpa(unsigned long dest_gpa, unsigned long src_gpa,
				unsigned int bytes)
{
	void *cb;
	void *dsr;
	int ret;

	STAT(copy_gpa);
	if (gru_get_cpu_resources(GRU_NUM_KERNEL_DSR_BYTES, &cb, &dsr))
		return MQE_BUG_NO_RESOURCES;
	gru_bcopy(cb, src_gpa, dest_gpa, gru_get_tri(dsr),
		  XTYPE_B, bytes, GRU_NUM_KERNEL_DSR_CL, IMA);
	ret = gru_wait(cb);
	gru_free_cpu_resources(cb, dsr);
	return ret;
}