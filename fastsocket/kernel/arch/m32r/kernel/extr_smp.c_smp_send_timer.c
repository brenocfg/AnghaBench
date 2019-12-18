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
 int /*<<< orphan*/  LOCAL_TIMER_IPI ; 
 int /*<<< orphan*/  send_IPI_allbutself (int /*<<< orphan*/ ,int) ; 

void smp_send_timer(void)
{
	send_IPI_allbutself(LOCAL_TIMER_IPI, 1);
}