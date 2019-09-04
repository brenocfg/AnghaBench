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

/* Variables and functions */
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ ) ; 
 int PTHREAD_CANCEL_DISABLE ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  lock ; 
 int log_fd ; 
 int /*<<< orphan*/  pthread_setcancelstate (int,int*) ; 

void closelog(void)
{
	int cs;
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &cs);
	LOCK(lock);
	close(log_fd);
	log_fd = -1;
	UNLOCK(lock);
	pthread_setcancelstate(cs, 0);
}