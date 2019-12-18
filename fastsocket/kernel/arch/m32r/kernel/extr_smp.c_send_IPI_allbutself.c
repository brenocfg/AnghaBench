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
typedef  int /*<<< orphan*/  cpumask_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_online_map ; 
 int /*<<< orphan*/  send_IPI_mask (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void send_IPI_allbutself(int ipi_num, int try)
{
	cpumask_t cpumask;

	cpumask = cpu_online_map;
	cpu_clear(smp_processor_id(), cpumask);

	send_IPI_mask(&cpumask, ipi_num, try);
}