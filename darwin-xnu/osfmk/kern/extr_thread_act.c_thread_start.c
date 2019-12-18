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
typedef  TYPE_1__* thread_t ;
struct TYPE_4__ {int /*<<< orphan*/  started; } ;

/* Variables and functions */
 int /*<<< orphan*/  THREAD_AWAKENED ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  clear_wait (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
thread_start(
	thread_t			thread)
{
	clear_wait(thread, THREAD_AWAKENED);
	thread->started = TRUE;
}