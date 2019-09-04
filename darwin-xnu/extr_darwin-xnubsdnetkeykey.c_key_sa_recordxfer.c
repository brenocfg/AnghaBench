#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timeval {int /*<<< orphan*/  tv_sec; } ;
struct secasvar {TYPE_2__* lft_c; } ;
struct TYPE_3__ {scalar_t__ len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct TYPE_4__ {int /*<<< orphan*/  sadb_lifetime_usetime; int /*<<< orphan*/  sadb_lifetime_allocations; int /*<<< orphan*/  sadb_lifetime_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  microtime (struct timeval*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  sadb_mutex ; 

void
key_sa_recordxfer(
				  struct secasvar *sav,
				  struct mbuf *m)
{
	
	
	if (!sav)
		panic("key_sa_recordxfer called with sav == NULL");
	if (!m)
		panic("key_sa_recordxfer called with m == NULL");
	if (!sav->lft_c)
		return;
	
	lck_mtx_lock(sadb_mutex);
	/*
	 * XXX Currently, there is a difference of bytes size
	 * between inbound and outbound processing.
	 */
	sav->lft_c->sadb_lifetime_bytes += m->m_pkthdr.len;
	/* to check bytes lifetime is done in key_timehandler(). */
	
	/*
	 * We use the number of packets as the unit of
	 * sadb_lifetime_allocations.  We increment the variable
	 * whenever {esp,ah}_{in,out}put is called.
	 */
	sav->lft_c->sadb_lifetime_allocations++;
	/* XXX check for expires? */
	
	/*
	 * NOTE: We record CURRENT sadb_lifetime_usetime by using wall clock,
	 * in seconds.  HARD and SOFT lifetime are measured by the time
	 * difference (again in seconds) from sadb_lifetime_usetime.
	 *
	 *	usetime
	 *	v     expire   expire
	 * -----+-----+--------+---> t
	 *	<--------------> HARD
	 *	<-----> SOFT
	 */
    {
		struct timeval tv;
		microtime(&tv);
		sav->lft_c->sadb_lifetime_usetime = tv.tv_sec;
		/* XXX check for expires? */
    }
	lck_mtx_unlock(sadb_mutex);
	
	return;
}