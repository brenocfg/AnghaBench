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

/* Variables and functions */
 int /*<<< orphan*/  COUNTERBUF_SIZE_PER_CPU ; 
 int /*<<< orphan*/  assert (struct cpu_data*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
kpc_unregister_cpu(struct cpu_data *cpu_data)
{
	assert(cpu_data);
	if (cpu_data->cpu_kpc_buf[0] != NULL) {
		kfree(cpu_data->cpu_kpc_buf[0], COUNTERBUF_SIZE_PER_CPU);
		cpu_data->cpu_kpc_buf[0] = NULL;
	}
	if (cpu_data->cpu_kpc_buf[1] != NULL) {
		kfree(cpu_data->cpu_kpc_buf[1], COUNTERBUF_SIZE_PER_CPU);
		cpu_data->cpu_kpc_buf[1] = NULL;
	}
	if (cpu_data->cpu_kpc_shadow != NULL) {
		kfree(cpu_data->cpu_kpc_shadow, COUNTERBUF_SIZE_PER_CPU);
		cpu_data->cpu_kpc_shadow = NULL;
	}
	if (cpu_data->cpu_kpc_reload != NULL) {	
		kfree(cpu_data->cpu_kpc_reload, COUNTERBUF_SIZE_PER_CPU);
		cpu_data->cpu_kpc_reload = NULL;
	}
}