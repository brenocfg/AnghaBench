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

/* Variables and functions */
 int /*<<< orphan*/  lockd_down () ; 
 int lockd_up () ; 
 int nfs4_state_start () ; 
 int nfsd_init_socks (unsigned short) ; 
 int nfsd_racache_init (int) ; 
 int /*<<< orphan*/  nfsd_racache_shutdown () ; 
 int nfsd_up ; 

__attribute__((used)) static int nfsd_startup(unsigned short port, int nrservs)
{
	int ret;

	if (nfsd_up)
		return 0;
	/*
	 * Readahead param cache - will no-op if it already exists.
	 * (Note therefore results will be suboptimal if number of
	 * threads is modified after nfsd start.)
	 */
	ret = nfsd_racache_init(2*nrservs);
	if (ret)
		return ret;
	ret = nfsd_init_socks(port);
	if (ret)
		goto out_racache;
	ret = lockd_up();
	if (ret)
		goto out_racache;
	ret = nfs4_state_start();
	if (ret)
		goto out_lockd;
	nfsd_up = true;
	return 0;
out_lockd:
	lockd_down();
out_racache:
	nfsd_racache_shutdown();
	return ret;
}