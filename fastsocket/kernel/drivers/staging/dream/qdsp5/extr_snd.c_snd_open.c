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
struct snd_ctxt {int opened; int /*<<< orphan*/  lock; int /*<<< orphan*/ * ept; } ;
struct inode {int dummy; } ;
struct file {struct snd_ctxt* private_data; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSM_RPC_UNINTERRUPTIBLE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RPC_SND_PROG ; 
 int /*<<< orphan*/  RPC_SND_VERS ; 
 int /*<<< orphan*/ * msm_rpc_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct snd_ctxt the_snd ; 

__attribute__((used)) static int snd_open(struct inode *inode, struct file *file)
{
	struct snd_ctxt *snd = &the_snd;
	int rc = 0;

	mutex_lock(&snd->lock);
	if (snd->opened == 0) {
		if (snd->ept == NULL) {
			snd->ept = msm_rpc_connect(RPC_SND_PROG, RPC_SND_VERS,
					MSM_RPC_UNINTERRUPTIBLE);
			if (IS_ERR(snd->ept)) {
				rc = PTR_ERR(snd->ept);
				snd->ept = NULL;
				pr_err("snd: failed to connect snd svc\n");
				goto err;
			}
		}
		file->private_data = snd;
		snd->opened = 1;
	} else {
		pr_err("snd already opened.\n");
		rc = -EBUSY;
	}

err:
	mutex_unlock(&snd->lock);
	return rc;
}