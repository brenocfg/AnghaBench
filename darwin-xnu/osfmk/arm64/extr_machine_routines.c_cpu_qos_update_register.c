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
typedef  int /*<<< orphan*/ * cpu_qos_update_t ;

/* Variables and functions */
 int /*<<< orphan*/ * cpu_qos_cb_default ; 
 int /*<<< orphan*/ * cpu_qos_update ; 

void cpu_qos_update_register(cpu_qos_update_t cpu_qos_cb) {
	if (cpu_qos_cb != NULL) {
		cpu_qos_update = cpu_qos_cb;
	} else {
		cpu_qos_update = cpu_qos_cb_default;
	}
}