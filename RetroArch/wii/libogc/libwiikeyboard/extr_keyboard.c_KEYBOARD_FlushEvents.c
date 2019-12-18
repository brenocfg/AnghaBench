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
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  _node ;

/* Variables and functions */
 scalar_t__ __lwp_queue_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _queue ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

s32 KEYBOARD_FlushEvents(void)
{
	s32 res;
	_node *n;

	res = 0;
	while (true) {
		n = (_node *) __lwp_queue_get(&_queue);

		if (!n)
			break;

		free(n);
		res++;
	}

	return res;
}