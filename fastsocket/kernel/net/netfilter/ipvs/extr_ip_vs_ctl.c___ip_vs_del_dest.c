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
struct ip_vs_dest {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  n_list; int /*<<< orphan*/  port; int /*<<< orphan*/  addr; int /*<<< orphan*/  af; TYPE_1__* svc; int /*<<< orphan*/  stats; } ;
struct TYPE_2__ {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_VS_DBG_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IP_VS_DBG_BUF (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ip_vs_rs_lock ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_vs_dest_trash ; 
 int /*<<< orphan*/  ip_vs_dst_reset (struct ip_vs_dest*) ; 
 int /*<<< orphan*/  ip_vs_kill_estimator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_vs_rs_unhash (struct ip_vs_dest*) ; 
 int /*<<< orphan*/  kfree (struct ip_vs_dest*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __ip_vs_del_dest(struct ip_vs_dest *dest)
{
	ip_vs_kill_estimator(&dest->stats);

	/*
	 *  Remove it from the d-linked list with the real services.
	 */
	write_lock_bh(&__ip_vs_rs_lock);
	ip_vs_rs_unhash(dest);
	write_unlock_bh(&__ip_vs_rs_lock);

	/*
	 *  Decrease the refcnt of the dest, and free the dest
	 *  if nobody refers to it (refcnt=0). Otherwise, throw
	 *  the destination into the trash.
	 */
	if (atomic_dec_and_test(&dest->refcnt)) {
		ip_vs_dst_reset(dest);
		/* simply decrease svc->refcnt here, let the caller check
		   and release the service if nobody refers to it.
		   Only user context can release destination and service,
		   and only one user context can update virtual service at a
		   time, so the operation here is OK */
		atomic_dec(&dest->svc->refcnt);
		kfree(dest);
	} else {
		IP_VS_DBG_BUF(3, "Moving dest %s:%u into trash, "
			      "dest->refcnt=%d\n",
			      IP_VS_DBG_ADDR(dest->af, &dest->addr),
			      ntohs(dest->port),
			      atomic_read(&dest->refcnt));
		list_add(&dest->n_list, &ip_vs_dest_trash);
		atomic_inc(&dest->refcnt);
	}
}