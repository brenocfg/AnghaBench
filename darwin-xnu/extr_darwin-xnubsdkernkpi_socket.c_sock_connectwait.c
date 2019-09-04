#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct timeval {long tv_sec; int tv_usec; } ;
struct timespec {long tv_sec; int tv_nsec; } ;
typedef  TYPE_3__* socket_t ;
typedef  int /*<<< orphan*/  lck_mtx_t ;
typedef  int integer_t ;
typedef  scalar_t__ errno_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_10__ {int so_state; scalar_t__ so_error; int /*<<< orphan*/  so_timeo; TYPE_2__* so_proto; } ;
struct TYPE_9__ {TYPE_1__* pr_domain; int /*<<< orphan*/ * (* pr_getlock ) (TYPE_3__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {int /*<<< orphan*/ * dom_mtx; } ;

/* Variables and functions */
 scalar_t__ EDOM ; 
 scalar_t__ EINPROGRESS ; 
 scalar_t__ EINVAL ; 
 scalar_t__ NSEC_PER_SEC ; 
 scalar_t__ NSEC_PER_USEC ; 
 int /*<<< orphan*/  PR_F_WILLUNLOCK ; 
 int /*<<< orphan*/  PSOCK ; 
 long SHRT_MAX ; 
 int SS_ISCONNECTED ; 
 int SS_ISCONNECTING ; 
 long hz ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct timespec*) ; 
 int /*<<< orphan*/  socket_lock (TYPE_3__*,int) ; 
 int /*<<< orphan*/  socket_unlock (TYPE_3__*,int) ; 
 int /*<<< orphan*/ * stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 

errno_t
sock_connectwait(socket_t sock, const struct timeval *tv)
{
	lck_mtx_t *mutex_held;
	errno_t	retval = 0;
	struct timespec ts;

	socket_lock(sock, 1);

	/* Check if we're already connected or if we've already errored out */
	if ((sock->so_state & SS_ISCONNECTING) == 0 || sock->so_error != 0) {
		if (sock->so_error != 0) {
			retval = sock->so_error;
			sock->so_error = 0;
		} else {
			if ((sock->so_state & SS_ISCONNECTED) != 0)
				retval = 0;
			else
				retval = EINVAL;
		}
		goto done;
	}

	/* copied translation from timeval to hertz from SO_RCVTIMEO handling */
	if (tv->tv_sec < 0 || tv->tv_sec > SHRT_MAX / hz ||
	    tv->tv_usec < 0 || tv->tv_usec >= 1000000) {
		retval = EDOM;
		goto done;
	}

	ts.tv_sec = tv->tv_sec;
	ts.tv_nsec = (tv->tv_usec * (integer_t)NSEC_PER_USEC);
	if ((ts.tv_sec + (ts.tv_nsec/(long)NSEC_PER_SEC))/100  >  SHRT_MAX)  {
		retval = EDOM;
		goto done;
	}

	if (sock->so_proto->pr_getlock != NULL)
		mutex_held = (*sock->so_proto->pr_getlock)(sock, PR_F_WILLUNLOCK);
	else
		mutex_held = sock->so_proto->pr_domain->dom_mtx;

	msleep((caddr_t)&sock->so_timeo, mutex_held,
	    PSOCK, "sock_connectwait", &ts);

	/* Check if we're still waiting to connect */
	if ((sock->so_state & SS_ISCONNECTING) && sock->so_error == 0) {
		retval = EINPROGRESS;
		goto done;
	}

	if (sock->so_error != 0) {
		retval = sock->so_error;
		sock->so_error = 0;
	}

done:
	socket_unlock(sock, 1);
	return (retval);
}