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
struct sockaddr {int sa_len; } ;
typedef  int /*<<< orphan*/ * socket_t ;
typedef  int errno_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FREE (struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_SONAME ; 
 int /*<<< orphan*/  memcpy (struct sockaddr*,struct sockaddr*,int) ; 
 int /*<<< orphan*/  socket_lock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  socket_unlock (int /*<<< orphan*/ *,int) ; 
 int sogetaddr_locked (int /*<<< orphan*/ *,struct sockaddr**,int /*<<< orphan*/ ) ; 

errno_t
sock_getsockname(socket_t sock, struct sockaddr	*sockname, int socknamelen)
{
	int error;
	struct sockaddr	*sa = NULL;

	if (sock == NULL || sockname == NULL || socknamelen < 0)
		return (EINVAL);

	socket_lock(sock, 1);
	error = sogetaddr_locked(sock, &sa, 0);
	socket_unlock(sock, 1);
	if (error == 0) {
		if (socknamelen > sa->sa_len)
			socknamelen = sa->sa_len;
		memcpy(sockname, sa, socknamelen);
		FREE(sa, M_SONAME);
	}
	return (error);
}