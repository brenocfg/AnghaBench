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
struct memstick_host {int /*<<< orphan*/  lock; scalar_t__ card; } ;

/* Variables and functions */
 int /*<<< orphan*/  memstick_detect_change (struct memstick_host*) ; 
 int memstick_power_on (struct memstick_host*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void memstick_resume_host(struct memstick_host *host)
{
	int rc = 0;

	mutex_lock(&host->lock);
	if (host->card)
		rc = memstick_power_on(host);
	mutex_unlock(&host->lock);

	if (!rc)
		memstick_detect_change(host);
}