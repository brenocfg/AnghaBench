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
struct pid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_LOCAL ; 
 int FD_CLOEXEC ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_CLOEXEC ; 
 int SOCK_CLOEXEC ; 
 int SOCK_STREAM ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 struct pid* malloc (int) ; 
 int pipe (int*) ; 
 int pipe2 (int*,int) ; 
 scalar_t__ socketpair (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ strchr (char const*,char) ; 
 scalar_t__ strrchr (char const*,char) ; 

__attribute__((used)) static struct pid *
pdes_get(int *pdes, const char **type)
{
	struct pid *cur;
	int flags = strchr(*type, 'e') ? O_CLOEXEC : 0;
	int serrno;

	if (strchr(*type, '+')) {
#ifndef SOCK_CLOEXEC
#define SOCK_CLOEXEC 0
#endif
		int stype = flags ? (SOCK_STREAM | SOCK_CLOEXEC) : SOCK_STREAM;
		*type = "r+";
		if (socketpair(AF_LOCAL, stype, 0, pdes) < 0)
			return NULL;
#if SOCK_CLOEXEC == 0
		fcntl(pdes[0], F_SETFD, FD_CLOEXEC);
		fcntl(pdes[1], F_SETFD, FD_CLOEXEC);
#endif
	} else  {
		*type = strrchr(*type, 'r') ? "r" : "w";
#if SOCK_CLOEXEC != 0
		if (pipe2(pdes, flags) == -1)
			return NULL;
#else
		if (pipe(pdes) == -1)
			return NULL;
		fcntl(pdes[0], F_SETFL, fcntl(pdes[0], F_GETFL) | flags);
		fcntl(pdes[1], F_SETFL, fcntl(pdes[1], F_GETFL) | flags);
#endif
	}

	if ((cur = malloc(sizeof(*cur))) != NULL)
		return cur;
	serrno = errno;
	(void)close(pdes[0]);
	(void)close(pdes[1]);
	errno = serrno;
	return NULL;
}