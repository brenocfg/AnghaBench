#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  network_socket_retval_t ;
struct TYPE_7__ {TYPE_4__* src; int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ network_socket ;
struct TYPE_6__ {int /*<<< orphan*/  common; } ;
struct TYPE_8__ {int /*<<< orphan*/  len; TYPE_1__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_STRLOC ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  IP_TOS ; 
 int /*<<< orphan*/  NETWORK_SOCKET_SUCCESS ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_KEEPALIVE ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  g_debug (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  g_strerror (int /*<<< orphan*/ ) ; 
 int getsockname (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ network_address_refresh_name (TYPE_4__*) ; 
 int /*<<< orphan*/  network_address_reset (TYPE_4__*) ; 
 int /*<<< orphan*/  setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

network_socket_retval_t network_socket_connect_setopts(network_socket *sock) {
#ifdef WIN32
	char val = 1;	/* Win32 setsockopt wants a const char* instead of the UNIX void*...*/
#else
	int val = 1;
#endif
	/**
	 * set the same options as the mysql client 
	 */
#ifdef IP_TOS
	val = 8;
	setsockopt(sock->fd, IPPROTO_IP,     IP_TOS, &val, sizeof(val));
#endif
	val = 1;
	setsockopt(sock->fd, IPPROTO_TCP,    TCP_NODELAY, &val, sizeof(val) );
	val = 1;
	setsockopt(sock->fd, SOL_SOCKET, SO_KEEPALIVE, &val, sizeof(val) );

	/* the listening side may be INADDR_ANY, let's get which address the client really connected to */
	if (-1 == getsockname(sock->fd, &sock->src->addr.common, &(sock->src->len))) {
		g_debug("%s: getsockname() failed: %s (%d)",
				G_STRLOC,
				g_strerror(errno),
				errno);
		network_address_reset(sock->src);
	} else if (network_address_refresh_name(sock->src)) {
		g_debug("%s: network_address_refresh_name() failed",
				G_STRLOC);
		network_address_reset(sock->src);
	}

	return NETWORK_SOCKET_SUCCESS;
}