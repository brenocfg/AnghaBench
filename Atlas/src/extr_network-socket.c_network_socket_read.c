#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int network_socklen_t ;
typedef  int /*<<< orphan*/  network_socket_retval_t ;
struct TYPE_12__ {scalar_t__ to_read; scalar_t__ socket_type; TYPE_3__* recv_queue_raw; TYPE_2__* dst; int /*<<< orphan*/  fd; } ;
typedef  TYPE_4__ network_socket ;
typedef  int gssize ;
struct TYPE_13__ {int len; int /*<<< orphan*/  str; } ;
struct TYPE_11__ {int len; scalar_t__ offset; int /*<<< orphan*/  chunks; } ;
struct TYPE_9__ {int /*<<< orphan*/  common; } ;
struct TYPE_10__ {int len; TYPE_1__ addr; } ;
typedef  TYPE_5__ GString ;

/* Variables and functions */
#define  EAGAIN 131 
#define  E_NET_CONNABORTED 130 
#define  E_NET_CONNRESET 129 
#define  E_NET_WOULDBLOCK 128 
 int /*<<< orphan*/  G_STRLOC ; 
 int /*<<< orphan*/  NETWORK_SOCKET_ERROR ; 
 int /*<<< orphan*/  NETWORK_SOCKET_SUCCESS ; 
 int /*<<< orphan*/  NETWORK_SOCKET_WAIT_FOR_EVENT ; 
 scalar_t__ SOCK_STREAM ; 
 int WSAGetLastError () ; 
 int errno ; 
 int /*<<< orphan*/  g_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_queue_push_tail (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  g_strerror (int) ; 
 TYPE_5__* g_string_sized_new (scalar_t__) ; 
 int recv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int recvfrom (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

network_socket_retval_t network_socket_read(network_socket *sock) {
	gssize len;

	if (sock->to_read > 0) {
		GString *packet = g_string_sized_new(sock->to_read);

		g_queue_push_tail(sock->recv_queue_raw->chunks, packet);

		if (sock->socket_type == SOCK_STREAM) {
			len = recv(sock->fd, packet->str, sock->to_read, 0);
		} else {
			/* UDP */
			network_socklen_t dst_len = sizeof(sock->dst->addr.common);
			len = recvfrom(sock->fd, packet->str, sock->to_read, 0, &(sock->dst->addr.common), &(dst_len));
			sock->dst->len = dst_len;
		}
		if (-1 == len) {
#ifdef _WIN32
			errno = WSAGetLastError();
#endif
			switch (errno) {
			case E_NET_CONNABORTED:
			case E_NET_CONNRESET: /** nothing to read, let's let ioctl() handle the close for us */
			case E_NET_WOULDBLOCK: /** the buffers are empty, try again later */
			case EAGAIN:     
				return NETWORK_SOCKET_WAIT_FOR_EVENT;
			default:
				g_debug("%s: recv() failed: %s (errno=%d)", G_STRLOC, g_strerror(errno), errno);
				return NETWORK_SOCKET_ERROR;
			}
		} else if (len == 0) {
			/**
			 * connection close
			 *
			 * let's call the ioctl() and let it handle it for use
			 */
			return NETWORK_SOCKET_WAIT_FOR_EVENT;
		}

		sock->to_read -= len;
		sock->recv_queue_raw->len += len;
#if 0
		sock->recv_queue_raw->offset = 0; /* offset into the first packet */
#endif
		packet->len = len;
	}

	return NETWORK_SOCKET_SUCCESS;
}