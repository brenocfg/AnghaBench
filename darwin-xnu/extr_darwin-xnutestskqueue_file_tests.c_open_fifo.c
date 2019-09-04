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
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  T_LOG (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int) ; 
 int fifo_read_fd ; 
 int open (char const*,int) ; 
 int /*<<< orphan*/  open_fifo_readside ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int 
open_fifo(const char *path, int *readfd, int *writefd) 
{
	pthread_t thread;
	int waitres;
	int res;
	int *tmpreadfd, tmpwritefd;
	
	fifo_read_fd = -1;
	res = pthread_create(&thread, 0, open_fifo_readside, (void*)path);
	if (res == 0) {
		if ((tmpwritefd = open(path, O_WRONLY)) == -1) {
			T_LOG("open(%s, O_WRONLY) failed: %d (%s)\n", path, errno, strerror(errno));
			return (-1);
		}
		waitres = pthread_join(thread, (void**) &tmpreadfd);
		
		fcntl(tmpwritefd, F_SETFL, O_WRONLY | O_NONBLOCK);
		
		if ((waitres == 0) && (tmpwritefd >= 0) && (*tmpreadfd >= 0)) {
			*readfd = *tmpreadfd;
			*writefd = tmpwritefd;
		} else {
			res = -1;	
		}
	}
	
	return res;
}