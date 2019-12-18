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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd_mutex ; 
 int /*<<< orphan*/ * nfsd_serv ; 
 int /*<<< orphan*/  svc_get (int /*<<< orphan*/ *) ; 
 int svc_pool_stats_open (int /*<<< orphan*/ *,struct file*) ; 

int nfsd_pool_stats_open(struct inode *inode, struct file *file)
{
	int ret;
	mutex_lock(&nfsd_mutex);
	if (nfsd_serv == NULL) {
		mutex_unlock(&nfsd_mutex);
		return -ENODEV;
	}
	/* bump up the psudo refcount while traversing */
	svc_get(nfsd_serv);
	ret = svc_pool_stats_open(nfsd_serv, file);
	mutex_unlock(&nfsd_mutex);
	return ret;
}