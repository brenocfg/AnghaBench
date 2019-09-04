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
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  _FREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** dtrace_clients ; 

void
dtrace_state_free(minor_t minor)
{
	dtrace_state_t *state = dtrace_clients[minor];
	dtrace_clients[minor] = NULL;
	_FREE(state, M_TEMP);
}