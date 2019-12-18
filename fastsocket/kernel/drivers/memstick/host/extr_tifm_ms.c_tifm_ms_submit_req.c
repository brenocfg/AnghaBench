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
struct tifm_ms {int /*<<< orphan*/  notify; } ;
struct memstick_host {int dummy; } ;

/* Variables and functions */
 struct tifm_ms* memstick_priv (struct memstick_host*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tifm_ms_submit_req(struct memstick_host *msh)
{
	struct tifm_ms *host = memstick_priv(msh);

	tasklet_schedule(&host->notify);
}