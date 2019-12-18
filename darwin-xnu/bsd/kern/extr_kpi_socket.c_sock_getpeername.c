#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int sa_len; } ;
typedef  TYPE_1__* socket_t ;
typedef  int errno_t ;
struct TYPE_6__ {int so_state; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  FREE (struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_SONAME ; 
 int SS_ISCONFIRMING ; 
 int SS_ISCONNECTED ; 
 int /*<<< orphan*/  memcpy (struct sockaddr*,struct sockaddr*,int) ; 
 int /*<<< orphan*/  socket_lock (TYPE_1__*,int) ; 
 int /*<<< orphan*/  socket_unlock (TYPE_1__*,int) ; 
 int sogetaddr_locked (TYPE_1__*,struct sockaddr**,int) ; 

errno_t
sock_getpeername(socket_t sock, struct sockaddr	*peername, int peernamelen)
{
	int error;
	struct sockaddr	*sa = NULL;

	if (sock == NULL || peername == NULL || peernamelen < 0)
		return (EINVAL);

	socket_lock(sock, 1);
	if (!(sock->so_state & (SS_ISCONNECTED|SS_ISCONFIRMING))) {
		socket_unlock(sock, 1);
		return (ENOTCONN);
	}
	error = sogetaddr_locked(sock, &sa, 1);
	socket_unlock(sock, 1);
	if (error == 0) {
		if (peernamelen > sa->sa_len)
			peernamelen = sa->sa_len;
		memcpy(peername, sa, peernamelen);
		FREE(sa, M_SONAME);
	}
	return (error);
}