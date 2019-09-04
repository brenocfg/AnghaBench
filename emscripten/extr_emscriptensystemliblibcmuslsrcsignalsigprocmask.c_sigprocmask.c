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
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int errno ; 
 int pthread_sigmask (int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int sigprocmask(int how, const sigset_t *restrict set, sigset_t *restrict old)
{
	int r = pthread_sigmask(how, set, old);
	if (!r) return r;
	errno = r;
	return -1;
}