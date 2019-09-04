#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ ss_size; int ss_flags; } ;
typedef  TYPE_1__ stack_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ MINSIGSTKSZ ; 
 int SS_DISABLE ; 
 int /*<<< orphan*/  SYS_sigaltstack ; 
 int /*<<< orphan*/  errno ; 
 int syscall (int /*<<< orphan*/ ,TYPE_1__ const*,TYPE_1__*) ; 

int sigaltstack(const stack_t *restrict ss, stack_t *restrict old)
{
	if (ss) {
		if (ss->ss_size < MINSIGSTKSZ) {
			errno = ENOMEM;
			return -1;
		}
		if (ss->ss_flags & ~SS_DISABLE) {
			errno = EINVAL;
			return -1;
		}
	}
	return syscall(SYS_sigaltstack, ss, old);
}