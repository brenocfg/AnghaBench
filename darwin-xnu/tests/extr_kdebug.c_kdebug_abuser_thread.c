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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  STRESS_DEBUGID ; 
 scalar_t__ continue_abuse ; 
 int /*<<< orphan*/  kdebug_trace (int /*<<< orphan*/ ,unsigned int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
kdebug_abuser_thread(void *ctx)
{
	unsigned int id = (unsigned int)ctx;
	uint64_t i = 0;
	while (continue_abuse) {
		kdebug_trace(STRESS_DEBUGID, id, i, 0, 0);
		i++;
	}

	return NULL;
}