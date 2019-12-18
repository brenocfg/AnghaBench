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
struct ip_vs_conn {int timeout; int flags; int /*<<< orphan*/  n_control; int /*<<< orphan*/  refcnt; int /*<<< orphan*/ * app; int /*<<< orphan*/  pe_data; int /*<<< orphan*/  pe; scalar_t__ control; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int HZ ; 
 int IP_VS_CONN_F_NO_CPORT ; 
 int IP_VS_CONN_F_ONE_PACKET ; 
 int /*<<< orphan*/  IP_VS_DBG (int,char*,int,int) ; 
 int IP_VS_STATE_MASTER ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_vs_conn_cachep ; 
 int /*<<< orphan*/  ip_vs_conn_count ; 
 int /*<<< orphan*/  ip_vs_conn_hash (struct ip_vs_conn*) ; 
 int /*<<< orphan*/  ip_vs_conn_no_cport_cnt ; 
 int /*<<< orphan*/  ip_vs_conn_put (struct ip_vs_conn*) ; 
 int /*<<< orphan*/  ip_vs_conn_unhash (struct ip_vs_conn*) ; 
 int /*<<< orphan*/  ip_vs_control_del (struct ip_vs_conn*) ; 
 int /*<<< orphan*/  ip_vs_pe_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_vs_sync_conn (struct ip_vs_conn*,int /*<<< orphan*/ ) ; 
 int ip_vs_sync_state ; 
 int /*<<< orphan*/  ip_vs_unbind_app (struct ip_vs_conn*) ; 
 int /*<<< orphan*/  ip_vs_unbind_dest (struct ip_vs_conn*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct ip_vs_conn*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  sysctl_sync_threshold () ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ip_vs_conn_expire(unsigned long data)
{
	struct ip_vs_conn *cp = (struct ip_vs_conn *)data;

	cp->timeout = 60*HZ;

	/*
	 *	hey, I'm using it
	 */
	atomic_inc(&cp->refcnt);

	/*
	 *	do I control anybody?
	 */
	if (atomic_read(&cp->n_control))
		goto expire_later;

	/*
	 *	unhash it if it is hashed in the conn table
	 */
	if (!ip_vs_conn_unhash(cp) && !(cp->flags & IP_VS_CONN_F_ONE_PACKET))
		goto expire_later;

	/*
	 *	refcnt==1 implies I'm the only one referrer
	 */
	if (likely(atomic_read(&cp->refcnt) == 1)) {
		/* delete the timer if it is activated by other users */
		if (timer_pending(&cp->timer))
			del_timer(&cp->timer);

		/* does anybody control me? */
		if (cp->control)
			ip_vs_control_del(cp);

/* RedHat: Future backport of nfct will need this:
		if (cp->flags & IP_VS_CONN_F_NFCT)
			ip_vs_conn_drop_conntrack(cp); */

		ip_vs_pe_put(cp->pe);
		kfree(cp->pe_data);
		if (unlikely(cp->app != NULL))
			ip_vs_unbind_app(cp);
		ip_vs_unbind_dest(cp);
		if (cp->flags & IP_VS_CONN_F_NO_CPORT)
			atomic_dec(&ip_vs_conn_no_cport_cnt);
		atomic_dec(&ip_vs_conn_count);

		kmem_cache_free(ip_vs_conn_cachep, cp);
		return;
	}

	/* hash it back to the table */
	ip_vs_conn_hash(cp);

  expire_later:
	IP_VS_DBG(7, "delayed: conn->refcnt-1=%d conn->n_control=%d\n",
		  atomic_read(&cp->refcnt)-1,
		  atomic_read(&cp->n_control));

	if (ip_vs_sync_state & IP_VS_STATE_MASTER)
		ip_vs_sync_conn(cp, sysctl_sync_threshold());

	ip_vs_conn_put(cp);
}