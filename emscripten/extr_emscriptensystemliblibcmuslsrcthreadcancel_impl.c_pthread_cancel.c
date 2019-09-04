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
typedef  TYPE_1__* pthread_t ;
struct TYPE_4__ {int /*<<< orphan*/  cancel; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGCANCEL ; 
 int /*<<< orphan*/  a_store (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_cancellation () ; 
 int pthread_kill (TYPE_1__*,int /*<<< orphan*/ ) ; 

int pthread_cancel(pthread_t t)
{
	static int init;
	if (!init) {
		init_cancellation();
		init = 1;
	}
	a_store(&t->cancel, 1);
	return pthread_kill(t, SIGCANCEL);
}