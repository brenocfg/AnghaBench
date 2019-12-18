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
 int GRU_NUM_TFM ; 
 int UV_MAX_INT_CORES ; 
 int smp_processor_id () ; 
 int uv_blade_processor_id () ; 
 int uv_cpu_core_number (int) ; 
 int uv_cpu_socket_number (int) ; 

int gru_cpu_fault_map_id(void)
{
#ifdef CONFIG_IA64
	return uv_blade_processor_id() % GRU_NUM_TFM;
#else
	int cpu = smp_processor_id();
	int id, core;

	core = uv_cpu_core_number(cpu);
	id = core + UV_MAX_INT_CORES * uv_cpu_socket_number(cpu);
	return id;
#endif
}