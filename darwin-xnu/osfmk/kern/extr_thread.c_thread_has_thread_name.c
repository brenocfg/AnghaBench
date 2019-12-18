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
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_3__ {scalar_t__ uthread; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  bsd_hasthreadname (scalar_t__) ; 

boolean_t
thread_has_thread_name(thread_t th)
{
	if ((th) && (th->uthread)) {
		return bsd_hasthreadname(th->uthread);
	}

	/*
	 * This is an odd case; clients may set the thread name based on the lack of
	 * a name, but in this context there is no uthread to attach the name to.
	 */
	return FALSE;
}