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
struct cpu_data {int /*<<< orphan*/ * cpu_kpc_reload; int /*<<< orphan*/ * cpu_kpc_shadow; int /*<<< orphan*/ ** cpu_kpc_buf; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTERBUF_SIZE_PER_CPU ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (struct cpu_data*) ; 
 void* kalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kpc_unregister_cpu (struct cpu_data*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

boolean_t
kpc_register_cpu(struct cpu_data *cpu_data)
{
	assert(cpu_data);
	assert(cpu_data->cpu_kpc_buf[0] == NULL);
	assert(cpu_data->cpu_kpc_buf[1] == NULL);
	assert(cpu_data->cpu_kpc_shadow == NULL);
	assert(cpu_data->cpu_kpc_reload == NULL);

	/*
	 * Buffers allocated through kpc_counterbuf_alloc() are large enough to
	 * store all PMCs values from all CPUs. This mimics the userspace API.
	 * This does not suit well with the per-CPU kpc buffers, since:
	 * 	1. Buffers don't need to be this large.
	 * 	2. The actual number of CPUs is not known at this point.
	 *
	 * CPUs are asked to callout into kpc when being registered, we'll
	 * allocate the memory here.
	 */

	if ((cpu_data->cpu_kpc_buf[0] = kalloc(COUNTERBUF_SIZE_PER_CPU)) == NULL)
		goto error;
	if ((cpu_data->cpu_kpc_buf[1] = kalloc(COUNTERBUF_SIZE_PER_CPU)) == NULL)
		goto error;
	if ((cpu_data->cpu_kpc_shadow = kalloc(COUNTERBUF_SIZE_PER_CPU)) == NULL)
		goto error;
	if ((cpu_data->cpu_kpc_reload = kalloc(COUNTERBUF_SIZE_PER_CPU)) == NULL)
		goto error;

	memset(cpu_data->cpu_kpc_buf[0], 0, COUNTERBUF_SIZE_PER_CPU);
	memset(cpu_data->cpu_kpc_buf[1], 0, COUNTERBUF_SIZE_PER_CPU);
	memset(cpu_data->cpu_kpc_shadow, 0, COUNTERBUF_SIZE_PER_CPU);
	memset(cpu_data->cpu_kpc_reload, 0, COUNTERBUF_SIZE_PER_CPU);

	/* success */
	return TRUE;

error:
	kpc_unregister_cpu(cpu_data);
	return FALSE;
}