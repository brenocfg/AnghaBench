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
struct socket {scalar_t__ so_retaincnt; int so_usecount; } ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*,struct socket*,int) ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int) ; 
 int soclose_locked (struct socket*) ; 

int
soclose(struct socket *so)
{
	int error = 0;
	socket_lock(so, 1);

	if (so->so_retaincnt == 0) {
		error = soclose_locked(so);
	} else {
		/*
		 * if the FD is going away, but socket is
		 * retained in kernel remove its reference
		 */
		so->so_usecount--;
		if (so->so_usecount < 2)
			panic("soclose: retaincnt non null and so=%p "
			    "usecount=%d\n", so, so->so_usecount);
	}
	socket_unlock(so, 1);
	return (error);
}