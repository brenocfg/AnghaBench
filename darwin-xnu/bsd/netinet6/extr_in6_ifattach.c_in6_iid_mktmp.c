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
typedef  int /*<<< orphan*/  u_int8_t ;
struct nd_ifinfo {int /*<<< orphan*/  lock; int /*<<< orphan*/  const* randomid; int /*<<< orphan*/ * randomseed1; int /*<<< orphan*/  randomseed0; scalar_t__ initialized; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  nullbuf ;

/* Variables and functions */
 struct nd_ifinfo* ND_IFINFO (struct ifnet*) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ bcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  in6_generate_tmp_iid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

void
in6_iid_mktmp(struct ifnet *ifp, u_int8_t *retbuf, const u_int8_t *baseid,
    int generate)
{
	u_int8_t nullbuf[8];
	struct nd_ifinfo *ndi = ND_IFINFO(ifp);

	VERIFY(ndi != NULL && ndi->initialized);
	lck_mtx_lock(&ndi->lock);
	bzero(nullbuf, sizeof (nullbuf));
	if (bcmp(ndi->randomid, nullbuf, sizeof (nullbuf)) == 0) {
		/* we've never created a random ID.  Create a new one. */
		generate = 1;
	}

	if (generate) {
		bcopy(baseid, ndi->randomseed1, sizeof (ndi->randomseed1));

		/* in6_generate_tmp_iid will update seedn and buf */
		(void) in6_generate_tmp_iid(ndi->randomseed0, ndi->randomseed1,
		    ndi->randomid);
	}

	bcopy(ndi->randomid, retbuf, 8);
	lck_mtx_unlock(&ndi->lock);
}