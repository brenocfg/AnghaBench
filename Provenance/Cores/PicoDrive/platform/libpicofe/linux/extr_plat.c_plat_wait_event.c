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
struct timeval {int tv_sec; int tv_usec; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  sleep (int) ; 

int plat_wait_event(int *fds_hnds, int count, int timeout_ms)
{
	struct timeval tv, *timeout = NULL;
	int i, ret, fdmax = -1;
	fd_set fdset;

	if (timeout_ms >= 0) {
		tv.tv_sec = timeout_ms / 1000;
		tv.tv_usec = (timeout_ms % 1000) * 1000;
		timeout = &tv;
	}

	FD_ZERO(&fdset);
	for (i = 0; i < count; i++) {
		if (fds_hnds[i] > fdmax) fdmax = fds_hnds[i];
		FD_SET(fds_hnds[i], &fdset);
	}

	ret = select(fdmax + 1, &fdset, NULL, NULL, timeout);
	if (ret == -1)
	{
		perror("plat_wait_event: select failed");
		sleep(1);
		return -1;
	}

	if (ret == 0)
		return -1; /* timeout */

	ret = -1;
	for (i = 0; i < count; i++)
		if (FD_ISSET(fds_hnds[i], &fdset))
			ret = fds_hnds[i];

	return ret;
}