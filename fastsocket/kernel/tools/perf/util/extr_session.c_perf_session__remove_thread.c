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
struct thread {int dummy; } ;
struct perf_session {int /*<<< orphan*/  host_machine; } ;

/* Variables and functions */
 int /*<<< orphan*/  machine__remove_thread (int /*<<< orphan*/ *,struct thread*) ; 

void perf_session__remove_thread(struct perf_session *session,
				 struct thread *th)
{
	/*
	 * FIXME: This one makes no sense, we need to remove the thread from
	 * the machine it belongs to, perf_session can have many machines, so
	 * doing it always on ->host_machine is wrong.  Fix when auditing all
	 * the 'perf kvm' code.
	 */
	machine__remove_thread(&session->host_machine, th);
}