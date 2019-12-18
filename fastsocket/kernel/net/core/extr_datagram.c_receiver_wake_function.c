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
typedef  int /*<<< orphan*/  wait_queue_t ;

/* Variables and functions */
 unsigned long POLLERR ; 
 unsigned long POLLIN ; 
 int autoremove_wake_function (int /*<<< orphan*/ *,unsigned int,int,void*) ; 

__attribute__((used)) static int receiver_wake_function(wait_queue_t *wait, unsigned mode, int sync,
				  void *key)
{
	unsigned long bits = (unsigned long)key;

	/*
	 * Avoid a wakeup if event not interesting for us
	 */
	if (bits && !(bits & (POLLIN | POLLERR)))
		return 0;
	return autoremove_wake_function(wait, mode, sync, key);
}