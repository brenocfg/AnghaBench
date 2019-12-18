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
typedef  int network_socklen_t ;
typedef  int /*<<< orphan*/  network_socket_retval_t ;
struct TYPE_3__ {scalar_t__ socket_type; int to_read; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ network_socket ;
typedef  int /*<<< orphan*/  b ;

/* Variables and functions */
 int /*<<< orphan*/  FIONREAD ; 
 int /*<<< orphan*/  G_STRLOC ; 
 int /*<<< orphan*/  NETWORK_SOCKET_ERROR ; 
 int /*<<< orphan*/  NETWORK_SOCKET_SUCCESS ; 
 scalar_t__ SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_NREAD ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  g_critical (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  g_strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ getsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

network_socket_retval_t network_socket_to_read(network_socket *sock) {
	int b = -1;

#ifdef SO_NREAD
	/* on MacOS X ioctl(..., FIONREAD) returns _more_ than what we have in the queue */
	if (sock->socket_type == SOCK_DGRAM) {
		network_socklen_t b_len = sizeof(b);

		if (0 != getsockopt(sock->fd, SOL_SOCKET, SO_NREAD, &b, &b_len)) {
			g_critical("%s: getsockopt(%d, SO_NREAD, ...) failed: %s (%d)",
					G_STRLOC,
					sock->fd,
					g_strerror(errno), errno);
			return NETWORK_SOCKET_ERROR;
		} else if (b < 0) {
			g_critical("%s: getsockopt(%d, SO_NREAD, ...) succeeded, but is negative: %d",
					G_STRLOC,
					sock->fd,
					b);

			return NETWORK_SOCKET_ERROR;
		} else {
			sock->to_read = b;
			return NETWORK_SOCKET_SUCCESS;
		}
	}
#endif

	if (0 != ioctl(sock->fd, FIONREAD, &b)) {
		g_critical("%s: ioctl(%d, FIONREAD, ...) failed: %s (%d)",
				G_STRLOC,
				sock->fd,
				g_strerror(errno), errno);
		return NETWORK_SOCKET_ERROR;
	} else if (b < 0) {
		g_critical("%s: ioctl(%d, FIONREAD, ...) succeeded, but is negative: %d",
				G_STRLOC,
				sock->fd,
				b);

		return NETWORK_SOCKET_ERROR;
	} else {
		sock->to_read = b;
		return NETWORK_SOCKET_SUCCESS;
	}

}