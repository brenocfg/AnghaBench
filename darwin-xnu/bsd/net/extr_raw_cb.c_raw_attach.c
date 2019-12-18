#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct socket {int dummy; } ;
struct TYPE_2__ {int sp_protocol; int /*<<< orphan*/  sp_family; } ;
struct rawcb {TYPE_1__ rcb_proto; struct socket* rcb_socket; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct rawcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOCK_DOM (struct socket*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  raw_mtx ; 
 int /*<<< orphan*/  raw_recvspace ; 
 int /*<<< orphan*/  raw_sendspace ; 
 int /*<<< orphan*/  rawcb_list ; 
 int soreserve (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rawcb* sotorawcb (struct socket*) ; 

int
raw_attach(struct socket *so, int proto)
{
	struct rawcb *rp = sotorawcb(so);
	int error;

	/*
	 * It is assumed that raw_attach is called
	 * after space has been allocated for the
	 * rawcb.
	 */
	if (rp == 0)
		return (ENOBUFS);
	error = soreserve(so, raw_sendspace, raw_recvspace);
	if (error)
		return (error);
	rp->rcb_socket = so;
	rp->rcb_proto.sp_family = SOCK_DOM(so);
	rp->rcb_proto.sp_protocol = proto;
	lck_mtx_lock(raw_mtx);
	LIST_INSERT_HEAD(&rawcb_list, rp, list);
	lck_mtx_unlock(raw_mtx);
	return (0);
}