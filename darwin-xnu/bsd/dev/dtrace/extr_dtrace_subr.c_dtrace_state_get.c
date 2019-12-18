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
typedef  int /*<<< orphan*/  dtrace_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 size_t DTRACE_NCLIENTS ; 
 int /*<<< orphan*/ ** dtrace_clients ; 

dtrace_state_t*
dtrace_state_get(minor_t minor)
{
	ASSERT(minor < DTRACE_NCLIENTS);
	return dtrace_clients[minor];
}