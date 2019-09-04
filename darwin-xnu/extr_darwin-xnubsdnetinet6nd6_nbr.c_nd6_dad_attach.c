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
struct ifaddr {int dummy; } ;
struct dadq {int dad_attached; scalar_t__ dad_lladdrlen; scalar_t__ dad_loopbackprobe; scalar_t__ dad_ns_lcount; scalar_t__ dad_ns_tcount; scalar_t__ dad_ns_ocount; scalar_t__ dad_na_icount; scalar_t__ dad_ns_icount; int /*<<< orphan*/  dad_count; struct ifaddr* dad_ifa; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAD_ADDREF_LOCKED (struct dadq*) ; 
 int /*<<< orphan*/  DAD_LOCK (struct dadq*) ; 
 int /*<<< orphan*/  DAD_UNLOCK (struct dadq*) ; 
 int /*<<< orphan*/  IFA_ADDREF (struct ifaddr*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct dadq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  dad6_mutex ; 
 int /*<<< orphan*/  dad_list ; 
 int /*<<< orphan*/  dadq ; 
 int /*<<< orphan*/  ip6_dad_count ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dadq *
nd6_dad_attach(struct dadq *dp, struct ifaddr *ifa)
{
	lck_mtx_lock(dad6_mutex);
	DAD_LOCK(dp);
	dp->dad_ifa = ifa;
	IFA_ADDREF(ifa);	/* for dad_ifa */
	dp->dad_count = ip6_dad_count;
	dp->dad_ns_icount = dp->dad_na_icount = 0;
	dp->dad_ns_ocount = dp->dad_ns_tcount = 0;
	dp->dad_ns_lcount = dp->dad_loopbackprobe = 0;
	VERIFY(!dp->dad_attached);
	dp->dad_attached = 1;
	dp->dad_lladdrlen = 0;
	DAD_ADDREF_LOCKED(dp);	/* for caller */
	DAD_ADDREF_LOCKED(dp);	/* for dadq_head list */
	TAILQ_INSERT_TAIL(&dadq, (struct dadq *)dp, dad_list);
	DAD_UNLOCK(dp);
	lck_mtx_unlock(dad6_mutex);

	return (dp);
}