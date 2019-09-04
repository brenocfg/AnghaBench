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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/ * socket_t ;
typedef  int /*<<< orphan*/  sock_evupcall ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  sock_catchevents_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_lock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  socket_unlock (int /*<<< orphan*/ *,int) ; 

errno_t
sock_catchevents(socket_t sock, sock_evupcall ecallback, void *econtext,
    u_int32_t emask)
{
	if (sock == NULL)
		return (EINVAL);

	socket_lock(sock, 1);
	sock_catchevents_locked(sock, ecallback, econtext, emask);
	socket_unlock(sock, 1);

	return (0);
}