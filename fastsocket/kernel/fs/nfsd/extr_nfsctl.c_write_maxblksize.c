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
struct file {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {scalar_t__ sv_nrthreads; } ;

/* Variables and functions */
 int EBUSY ; 
 int NFSSVC_MAXBLKSIZE ; 
 int /*<<< orphan*/  SIMPLE_TRANSACTION_LIMIT ; 
 int get_int (char**,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nfsd_max_blksize ; 
 int /*<<< orphan*/  nfsd_mutex ; 
 TYPE_1__* nfsd_serv ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t write_maxblksize(struct file *file, char *buf, size_t size)
{
	char *mesg = buf;
	if (size > 0) {
		int bsize;
		int rv = get_int(&mesg, &bsize);
		if (rv)
			return rv;
		/* force bsize into allowed range and
		 * required alignment.
		 */
		if (bsize < 1024)
			bsize = 1024;
		if (bsize > NFSSVC_MAXBLKSIZE)
			bsize = NFSSVC_MAXBLKSIZE;
		bsize &= ~(1024-1);
		mutex_lock(&nfsd_mutex);
		if (nfsd_serv && nfsd_serv->sv_nrthreads) {
			mutex_unlock(&nfsd_mutex);
			return -EBUSY;
		}
		nfsd_max_blksize = bsize;
		mutex_unlock(&nfsd_mutex);
	}

	return scnprintf(buf, SIMPLE_TRANSACTION_LIMIT, "%d\n",
							nfsd_max_blksize);
}