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
typedef  size_t minor_t ;

/* Variables and functions */
 int DTRACE_NCLIENTS ; 
 int atomic_add_32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ ** dtrace_clients ; 
 int /*<<< orphan*/  next_minor ; 

minor_t
dtrace_state_reserve(void)
{
	for (int i = 0; i < DTRACE_NCLIENTS; i++) {
		minor_t minor = atomic_add_32(&next_minor, 1) % DTRACE_NCLIENTS;
		if (dtrace_clients[minor] == NULL)
			return minor;
	}
	return 0;
}