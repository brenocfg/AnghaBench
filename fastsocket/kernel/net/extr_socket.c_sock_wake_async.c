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
struct socket {int /*<<< orphan*/  fasync_list; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  SIGURG ; 
 int /*<<< orphan*/  SOCK_ASYNC_NOSPACE ; 
 int /*<<< orphan*/  SOCK_ASYNC_WAITDATA ; 
#define  SOCK_WAKE_IO 131 
#define  SOCK_WAKE_SPACE 130 
#define  SOCK_WAKE_URG 129 
#define  SOCK_WAKE_WAITD 128 
 int /*<<< orphan*/  __kill_fasync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int sock_wake_async(struct socket *sock, int how, int band)
{
	if (!sock || !sock->fasync_list)
		return -1;
	switch (how) {
	case SOCK_WAKE_WAITD:
		if (test_bit(SOCK_ASYNC_WAITDATA, &sock->flags))
			break;
		goto call_kill;
	case SOCK_WAKE_SPACE:
		if (!test_and_clear_bit(SOCK_ASYNC_NOSPACE, &sock->flags))
			break;
		/* fall through */
	case SOCK_WAKE_IO:
call_kill:
		__kill_fasync(sock->fasync_list, SIGIO, band);
		break;
	case SOCK_WAKE_URG:
		__kill_fasync(sock->fasync_list, SIGURG, band);
	}
	return 0;
}