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
typedef  int /*<<< orphan*/  u_long ;
struct socket {int dummy; } ;
struct proc {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int ifioctl (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct proc*) ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int /*<<< orphan*/ ) ; 

int
ifioctllocked(struct socket *so, u_long cmd, caddr_t data, struct proc *p)
{
	int error;

	socket_unlock(so, 0);
	error = ifioctl(so, cmd, data, p);
	socket_lock(so, 0);
	return (error);
}