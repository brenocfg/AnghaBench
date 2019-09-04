#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* socket_t ;
struct TYPE_5__ {int so_state; } ;

/* Variables and functions */
 int SS_ISCONNECTED ; 
 int /*<<< orphan*/  socket_lock (TYPE_1__*,int) ; 
 int /*<<< orphan*/  socket_unlock (TYPE_1__*,int) ; 

int
sock_isconnected(socket_t sock)
{
	int retval;

	socket_lock(sock, 1);
	retval = ((sock->so_state & SS_ISCONNECTED) ? 1 : 0);
	socket_unlock(sock, 1);
	return (retval);
}