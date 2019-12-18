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
 int /*<<< orphan*/  LWP_InitQueue (int /*<<< orphan*/ *) ; 
 int exi_wait_inited ; 
 int /*<<< orphan*/  time_exi_wait ; 

void __timesystem_init()
{
	if(!exi_wait_inited) {
		exi_wait_inited = 1;
		LWP_InitQueue(&time_exi_wait);
	}
}