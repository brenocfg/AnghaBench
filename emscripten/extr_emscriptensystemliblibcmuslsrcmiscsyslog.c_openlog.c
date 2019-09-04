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
 int LOG_NDELAY ; 
 int PTHREAD_CANCEL_DISABLE ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __openlog () ; 
 int /*<<< orphan*/  lock ; 
 int log_facility ; 
 scalar_t__ log_fd ; 
 scalar_t__* log_ident ; 
 int log_opt ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char const*,size_t) ; 
 int /*<<< orphan*/  pthread_setcancelstate (int,int*) ; 
 size_t strnlen (char const*,int) ; 

void openlog(const char *ident, int opt, int facility)
{
	int cs;
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &cs);
	LOCK(lock);

	if (ident) {
		size_t n = strnlen(ident, sizeof log_ident - 1);
		memcpy(log_ident, ident, n);
		log_ident[n] = 0;
	} else {
		log_ident[0] = 0;
	}
	log_opt = opt;
	log_facility = facility;

	if ((opt & LOG_NDELAY) && log_fd<0) __openlog();

	UNLOCK(lock);
	pthread_setcancelstate(cs, 0);
}