#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  t; } ;

/* Variables and functions */
 int NR_CPUS ; 
 TYPE_1__* cvm_oct_tasklet ; 
 int /*<<< orphan*/  cvm_oct_tasklet_rx ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cvm_oct_rx_initialize(void)
{
	int i;
	/* Initialize all of the tasklets */
	for (i = 0; i < NR_CPUS; i++)
		tasklet_init(&cvm_oct_tasklet[i].t, cvm_oct_tasklet_rx, 0);
}