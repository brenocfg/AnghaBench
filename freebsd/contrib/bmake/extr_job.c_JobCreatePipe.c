#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* jobPipe; } ;
typedef  TYPE_1__ Job ;

/* Variables and functions */
 int FD_CLOEXEC ; 
 int /*<<< orphan*/  F_DUPFD ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  Punt (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int pipe (int*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
JobCreatePipe(Job *job, int minfd)
{
    int i, fd, flags;

    if (pipe(job->jobPipe) == -1)
	Punt("Cannot create pipe: %s", strerror(errno));

    for (i = 0; i < 2; i++) {
       /* Avoid using low numbered fds */
       fd = fcntl(job->jobPipe[i], F_DUPFD, minfd);
       if (fd != -1) {
	   close(job->jobPipe[i]);
	   job->jobPipe[i] = fd;
       }
    }
    
    /* Set close-on-exec flag for both */
    if (fcntl(job->jobPipe[0], F_SETFD, FD_CLOEXEC) == -1)
	Punt("Cannot set close-on-exec: %s", strerror(errno));
    if (fcntl(job->jobPipe[1], F_SETFD, FD_CLOEXEC) == -1)
	Punt("Cannot set close-on-exec: %s", strerror(errno));

    /*
     * We mark the input side of the pipe non-blocking; we poll(2) the
     * pipe when we're waiting for a job token, but we might lose the
     * race for the token when a new one becomes available, so the read 
     * from the pipe should not block.
     */
    flags = fcntl(job->jobPipe[0], F_GETFL, 0);
    if (flags == -1)
	Punt("Cannot get flags: %s", strerror(errno));
    flags |= O_NONBLOCK;
    if (fcntl(job->jobPipe[0], F_SETFL, flags) == -1)
	Punt("Cannot set flags: %s", strerror(errno));
}