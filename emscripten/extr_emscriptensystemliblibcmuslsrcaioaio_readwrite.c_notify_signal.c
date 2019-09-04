#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sigevent {int /*<<< orphan*/  sigev_value; int /*<<< orphan*/  sigev_signo; } ;
struct TYPE_4__ {int /*<<< orphan*/  si_signo; int /*<<< orphan*/  si_pid; int /*<<< orphan*/  si_uid; int /*<<< orphan*/  si_code; int /*<<< orphan*/  si_value; } ;
typedef  TYPE_1__ siginfo_t ;
struct TYPE_5__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  SI_ASYNCIO ; 
 int /*<<< orphan*/  SYS_rt_sigqueueinfo ; 
 TYPE_3__* __pthread_self () ; 
 int /*<<< orphan*/  __syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  getuid () ; 

__attribute__((used)) static void notify_signal(struct sigevent *sev)
{
	siginfo_t si = {
		.si_signo = sev->sigev_signo,
		.si_value = sev->sigev_value,
		.si_code = SI_ASYNCIO,
		.si_pid = __pthread_self()->pid,
		.si_uid = getuid()
	};
	__syscall(SYS_rt_sigqueueinfo, si.si_pid, si.si_signo, &si);
}