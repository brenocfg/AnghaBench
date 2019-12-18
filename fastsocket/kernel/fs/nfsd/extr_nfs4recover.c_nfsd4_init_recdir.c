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
struct cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int O_DIRECTORY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/ * filp_open (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_reset_creds (struct cred const*) ; 
 int nfs4_save_creds (struct cred const**) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/ * rec_file ; 

void
nfsd4_init_recdir(char *rec_dirname)
{
	const struct cred *original_cred;
	int status;

	printk("NFSD: Using %s as the NFSv4 state recovery directory\n",
			rec_dirname);

	BUG_ON(rec_file);

	status = nfs4_save_creds(&original_cred);
	if (status < 0) {
		printk("NFSD: Unable to change credentials to find recovery"
		       " directory: error %d\n",
		       status);
		return;
	}

	rec_file = filp_open(rec_dirname, O_RDONLY | O_DIRECTORY, 0);
	if (IS_ERR(rec_file)) {
		printk("NFSD: unable to find recovery directory %s\n",
				rec_dirname);
		rec_file = NULL;
	}

	nfs4_reset_creds(original_cred);
}