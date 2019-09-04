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
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  NAME_MAX ; 
 int O_CLOEXEC ; 
 int O_NOFOLLOW ; 
 int O_NONBLOCK ; 
 int PTHREAD_CANCEL_DISABLE ; 
 char* __shm_mapname (char const*,char*) ; 
 int open (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_setcancelstate (int,int*) ; 

int shm_open(const char *name, int flag, mode_t mode)
{
	int cs;
	char buf[NAME_MAX+10];
	if (!(name = __shm_mapname(name, buf))) return -1;
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &cs);
	int fd = open(name, flag|O_NOFOLLOW|O_CLOEXEC|O_NONBLOCK, mode);
	pthread_setcancelstate(cs, 0);
	return fd;
}