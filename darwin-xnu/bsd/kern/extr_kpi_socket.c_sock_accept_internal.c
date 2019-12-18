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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socket_t ;
typedef  int /*<<< orphan*/  sock_upcall ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  sock_accept_common (int /*<<< orphan*/ ,struct sockaddr*,int,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int) ; 

errno_t
sock_accept_internal(socket_t sock, struct sockaddr *from, int fromlen, int flags,
    sock_upcall callback, void *cookie, socket_t *new_sock)
{
	return (sock_accept_common(sock, from, fromlen, flags,
	    callback, cookie, new_sock, true));
}