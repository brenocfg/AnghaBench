#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pollfd {int fd; int revents; } ;
struct TYPE_2__ {int secure; } ;

/* Variables and functions */
 size_t AT_EGID ; 
 size_t AT_EUID ; 
 size_t AT_GID ; 
 size_t AT_RANDOM ; 
 size_t AT_SECURE ; 
 size_t AT_UID ; 
 int O_LARGEFILE ; 
 int O_RDWR ; 
 int POLLNVAL ; 
 int /*<<< orphan*/  SYS_open ; 
 int /*<<< orphan*/  SYS_poll ; 
 int /*<<< orphan*/  __init_ssp (void*) ; 
 int /*<<< orphan*/  __syscall (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  a_crash () ; 
 TYPE_1__ libc ; 

void __init_security(size_t *aux)
{
	struct pollfd pfd[3] = { {.fd=0}, {.fd=1}, {.fd=2} };
	int i;

#ifndef SHARED
	__init_ssp((void *)aux[AT_RANDOM]);
#endif

	if (aux[AT_UID]==aux[AT_EUID] && aux[AT_GID]==aux[AT_EGID]
		&& !aux[AT_SECURE]) return;

	__syscall(SYS_poll, pfd, 3, 0);
	for (i=0; i<3; i++) if (pfd[i].revents&POLLNVAL)
		if (__syscall(SYS_open, "/dev/null", O_RDWR|O_LARGEFILE)<0)
			a_crash();
	libc.secure = 1;
}