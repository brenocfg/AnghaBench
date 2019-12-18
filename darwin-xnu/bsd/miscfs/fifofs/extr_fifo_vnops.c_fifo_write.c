#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vnop_write_args {int a_ioflag; TYPE_3__* a_vp; TYPE_2__* a_uio; } ;
struct socket {int dummy; } ;
struct sockaddr {int dummy; } ;
struct mbuf {int dummy; } ;
struct TYPE_6__ {TYPE_1__* v_fifoinfo; } ;
struct TYPE_5__ {scalar_t__ uio_rw; } ;
struct TYPE_4__ {struct socket* fi_writesock; } ;

/* Variables and functions */
 int IO_NDELAY ; 
 int /*<<< orphan*/  MSG_NBIO ; 
 scalar_t__ UIO_WRITE ; 
 int /*<<< orphan*/  lock_vnode_and_post (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int sosend (struct socket*,struct sockaddr*,TYPE_2__*,int /*<<< orphan*/ *,struct mbuf*,int /*<<< orphan*/ ) ; 

int
fifo_write(struct vnop_write_args *ap)
{
	struct socket *wso = ap->a_vp->v_fifoinfo->fi_writesock;
	int error;

#if DIAGNOSTIC
	if (ap->a_uio->uio_rw != UIO_WRITE)
		panic("fifo_write mode");
#endif
	error = sosend(wso, (struct sockaddr *)0, ap->a_uio, NULL,
		       (struct mbuf *)0, (ap->a_ioflag & IO_NDELAY) ? MSG_NBIO : 0);
	if (error == 0)
		lock_vnode_and_post(ap->a_vp, 0);

	return (error);
}