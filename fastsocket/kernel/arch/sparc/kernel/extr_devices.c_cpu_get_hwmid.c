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
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  cpu_mid_prop () ; 
 int prom_getintdefault (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cpu_get_hwmid(int prom_node)
{
	return prom_getintdefault(prom_node, cpu_mid_prop(), -ENODEV);
}