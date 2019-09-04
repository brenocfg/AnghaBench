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
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock ; 
 int log_mask ; 

int setlogmask(int maskpri)
{
	LOCK(lock);
	int ret = log_mask;
	if (maskpri) log_mask = maskpri;
	UNLOCK(lock);
	return ret;
}