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
struct timeval {long tv_sec; long tv_usec; } ;
struct pollfd {int revents; int events; int fd; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int FD_SETSIZE ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int POLLIN ; 
 int POLLOUT ; 
 int /*<<< orphan*/  Punt (char*) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct timeval*) ; 

int
emul_poll(struct pollfd *fd, int nfd, int timeout)
{
    fd_set rfds, wfds;
    int i, maxfd, nselect, npoll;
    struct timeval tv, *tvp;
    long usecs;

    FD_ZERO(&rfds);
    FD_ZERO(&wfds);

    maxfd = -1;
    for (i = 0; i < nfd; i++) {
	fd[i].revents = 0;

	if (fd[i].events & POLLIN)
	    FD_SET(fd[i].fd, &rfds);

	if (fd[i].events & POLLOUT)
	    FD_SET(fd[i].fd, &wfds);

	if (fd[i].fd > maxfd)
	    maxfd = fd[i].fd;
    }
    
    if (maxfd >= FD_SETSIZE) {
	Punt("Ran out of fd_set slots; " 
	     "recompile with a larger FD_SETSIZE.");
    }

    if (timeout < 0) {
	tvp = NULL;
    } else {
	usecs = timeout * 1000;
	tv.tv_sec = usecs / 1000000;
	tv.tv_usec = usecs % 1000000;
        tvp = &tv;
    }

    nselect = select(maxfd + 1, &rfds, &wfds, 0, tvp);

    if (nselect <= 0)
	return nselect;

    npoll = 0;
    for (i = 0; i < nfd; i++) {
	if (FD_ISSET(fd[i].fd, &rfds))
	    fd[i].revents |= POLLIN;

	if (FD_ISSET(fd[i].fd, &wfds))
	    fd[i].revents |= POLLOUT;

	if (fd[i].revents)
	    npoll++;
    }

    return npoll;
}