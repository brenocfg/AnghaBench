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
struct socket {int dummy; } ;
struct proc {int dummy; } ;
struct disconnectx_args {int s; int /*<<< orphan*/  cid; int /*<<< orphan*/  aid; } ;

/* Variables and functions */
 int EBADF ; 
 int /*<<< orphan*/  file_drop (int) ; 
 int file_socket (int,struct socket**) ; 
 int sodisconnectx (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
disconnectx_nocancel(struct proc *p, struct disconnectx_args *uap, int *retval)
{
#pragma unused(p, retval)
	struct socket *so;
	int fd = uap->s;
	int error;

	error = file_socket(fd, &so);
	if (error != 0)
		return (error);
	if (so == NULL) {
		error = EBADF;
		goto out;
	}

	error = sodisconnectx(so, uap->aid, uap->cid);
out:
	file_drop(fd);
	return (error);
}