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
typedef  int /*<<< orphan*/  lwp_node ;
typedef  int /*<<< orphan*/  keyboard_event ;
struct TYPE_3__ {int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ _node ;

/* Variables and functions */
 int /*<<< orphan*/  __lwp_queue_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _queue ; 
 TYPE_1__* malloc (int) ; 

__attribute__((used)) static s32 _kbd_addEvent(const keyboard_event *event) {
	_node *n = malloc(sizeof(_node));
	n->event = *event;

	__lwp_queue_append(&_queue, (lwp_node*) n);

	return 1;
}