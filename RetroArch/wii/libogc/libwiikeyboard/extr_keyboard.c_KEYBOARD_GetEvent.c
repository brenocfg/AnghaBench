#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int s32 ;
typedef  int /*<<< orphan*/  keyboard_event ;
struct TYPE_3__ {int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ _node ;

/* Variables and functions */
 scalar_t__ __lwp_queue_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _queue ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

s32 KEYBOARD_GetEvent(keyboard_event *event)
{
	_node *n = (_node *) __lwp_queue_get(&_queue);

	if (!n)
		return 0;

	*event = n->event;

	free(n);

	return 1;
}