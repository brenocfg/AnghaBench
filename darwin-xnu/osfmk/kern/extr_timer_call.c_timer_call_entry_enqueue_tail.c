#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  timer_call_t ;
struct TYPE_4__ {int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ mpqueue_head_t ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE (TYPE_1__*) ; 
 int /*<<< orphan*/  TCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_entry_enqueue_tail (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ void
timer_call_entry_enqueue_tail(
	timer_call_t			entry,
	mpqueue_head_t			*queue)
{
	call_entry_enqueue_tail(TCE(entry), QUEUE(queue));
	queue->count++;
	return;
}