#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long mode; } ;
struct TYPE_4__ {TYPE_1__ seccomp; } ;

/* Variables and functions */
 long EINVAL ; 
 long EPERM ; 
 unsigned long NR_SECCOMP_MODES ; 
 int /*<<< orphan*/  TIF_SECCOMP ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  disable_TSC () ; 
 int /*<<< orphan*/  set_thread_flag (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (unsigned long) ; 

long prctl_set_seccomp(unsigned long seccomp_mode)
{
	long ret;

	/* can set it only once to be even more secure */
	ret = -EPERM;
	if (unlikely(current->seccomp.mode))
		goto out;

	ret = -EINVAL;
	if (seccomp_mode && seccomp_mode <= NR_SECCOMP_MODES) {
		current->seccomp.mode = seccomp_mode;
		set_thread_flag(TIF_SECCOMP);
#ifdef TIF_NOTSC
		disable_TSC();
#endif
		ret = 0;
	}

 out:
	return ret;
}