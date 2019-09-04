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
struct knote {scalar_t__ kn_data; } ;
struct kevent_internal_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  proc_klist_lock () ; 
 int /*<<< orphan*/  proc_klist_unlock () ; 

__attribute__((used)) static int
filt_signaltouch(
	struct knote *kn,
	struct kevent_internal_s *kev)
{
#pragma unused(kev)

	int res;

	proc_klist_lock();

	/*
	 * No data to save - just capture if it is already fired
	 */
	res = (kn->kn_data > 0);

	proc_klist_unlock();

	return res;
}