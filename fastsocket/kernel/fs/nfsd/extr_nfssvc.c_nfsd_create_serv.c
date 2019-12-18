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
struct sysinfo {int totalram; } ;

/* Variables and functions */
 int ENOMEM ; 
 int NFSSVC_MAXBLKSIZE ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  do_gettimeofday (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd ; 
 int /*<<< orphan*/  nfsd_last_thread ; 
 int nfsd_max_blksize ; 
 int /*<<< orphan*/  nfsd_mutex ; 
 int /*<<< orphan*/  nfsd_program ; 
 int /*<<< orphan*/  nfsd_reset_versions () ; 
 int /*<<< orphan*/ * nfsd_serv ; 
 int /*<<< orphan*/  nfssvc_boot ; 
 int /*<<< orphan*/  set_max_drc () ; 
 int /*<<< orphan*/  si_meminfo (struct sysinfo*) ; 
 int /*<<< orphan*/ * svc_create_pooled (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_get (int /*<<< orphan*/ *) ; 

int nfsd_create_serv(void)
{
	int err = 0;

	WARN_ON(!mutex_is_locked(&nfsd_mutex));
	if (nfsd_serv) {
		svc_get(nfsd_serv);
		return 0;
	}
	if (nfsd_max_blksize == 0) {
		/* choose a suitable default */
		struct sysinfo i;
		si_meminfo(&i);
		/* Aim for 1/4096 of memory per thread
		 * This gives 1MB on 4Gig machines
		 * But only uses 32K on 128M machines.
		 * Bottom out at 8K on 32M and smaller.
		 * Of course, this is only a default.
		 */
		nfsd_max_blksize = NFSSVC_MAXBLKSIZE;
		i.totalram <<= PAGE_SHIFT - 12;
		while (nfsd_max_blksize > i.totalram &&
		       nfsd_max_blksize >= 8*1024*2)
			nfsd_max_blksize /= 2;
	}
	nfsd_reset_versions();

	nfsd_serv = svc_create_pooled(&nfsd_program, nfsd_max_blksize,
				      nfsd_last_thread, nfsd, THIS_MODULE);
	if (nfsd_serv == NULL)
		return -ENOMEM;

	set_max_drc();
	do_gettimeofday(&nfssvc_boot);		/* record boot time */
	return err;
}