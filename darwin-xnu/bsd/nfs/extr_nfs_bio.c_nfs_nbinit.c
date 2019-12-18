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
 int /*<<< orphan*/  LCK_ATTR_NULL ; 
 int /*<<< orphan*/  LCK_GRP_ATTR_NULL ; 
 int /*<<< orphan*/  M_TEMP ; 
 int NFS_RWSIZE ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashinit (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_alloc_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_buf_lck_grp ; 
 int /*<<< orphan*/  nfs_buf_mutex ; 
 scalar_t__ nfs_nbdwrite ; 
 scalar_t__ nfsbufcnt ; 
 int /*<<< orphan*/  nfsbufdelwri ; 
 scalar_t__ nfsbufdelwricnt ; 
 int /*<<< orphan*/  nfsbuffree ; 
 scalar_t__ nfsbuffreecnt ; 
 int /*<<< orphan*/  nfsbuffreemeta ; 
 scalar_t__ nfsbuffreemetacnt ; 
 int /*<<< orphan*/  nfsbufhash ; 
 int /*<<< orphan*/  nfsbufhashtbl ; 
 int nfsbufmax ; 
 scalar_t__ nfsbufmetacnt ; 
 int nfsbufmetamax ; 
 int nfsbufmin ; 
 scalar_t__ nfsneedbuffer ; 
 int sane_size ; 

void
nfs_nbinit(void)
{
	nfs_buf_lck_grp = lck_grp_alloc_init("nfs_buf", LCK_GRP_ATTR_NULL);
	nfs_buf_mutex = lck_mtx_alloc_init(nfs_buf_lck_grp, LCK_ATTR_NULL);

	nfsbufcnt = nfsbufmetacnt =
	nfsbuffreecnt = nfsbuffreemetacnt = nfsbufdelwricnt = 0;
	nfsbufmin = 128;
	/* size nfsbufmax to cover at most half sane_size (w/default buf size) */
	nfsbufmax = (sane_size >> PAGE_SHIFT) / (2 * (NFS_RWSIZE >> PAGE_SHIFT));
	nfsbufmetamax = nfsbufmax / 4;
	nfsneedbuffer = 0;
	nfs_nbdwrite = 0;

	nfsbufhashtbl = hashinit(nfsbufmax/4, M_TEMP, &nfsbufhash);
	TAILQ_INIT(&nfsbuffree);
	TAILQ_INIT(&nfsbuffreemeta);
	TAILQ_INIT(&nfsbufdelwri);

}