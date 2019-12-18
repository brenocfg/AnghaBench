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
struct ips_driver {int __cpu_turbo_on; scalar_t__ turbo_toggle_allowed; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_disable_cpu_turbo ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,struct ips_driver*,int) ; 

__attribute__((used)) static void ips_disable_cpu_turbo(struct ips_driver *ips)
{
	/* Already off, leave it */
	if (!ips->__cpu_turbo_on)
		return;

	if (ips->turbo_toggle_allowed)
		on_each_cpu(do_disable_cpu_turbo, ips, 1);

	ips->__cpu_turbo_on = false;
}