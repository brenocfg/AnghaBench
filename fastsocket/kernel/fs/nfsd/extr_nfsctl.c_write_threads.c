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
struct file {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NFS_PORT ; 
 int /*<<< orphan*/  SIMPLE_TRANSACTION_LIMIT ; 
 int get_int (char**,int*) ; 
 int nfsd_nrthreads () ; 
 int nfsd_svc (int /*<<< orphan*/ ,int) ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t write_threads(struct file *file, char *buf, size_t size)
{
	char *mesg = buf;
	int rv;
	if (size > 0) {
		int newthreads;
		rv = get_int(&mesg, &newthreads);
		if (rv)
			return rv;
		if (newthreads < 0)
			return -EINVAL;
		rv = nfsd_svc(NFS_PORT, newthreads);
		if (rv < 0)
			return rv;
	} else
		rv = nfsd_nrthreads();

	return scnprintf(buf, SIMPLE_TRANSACTION_LIMIT, "%d\n", rv);
}