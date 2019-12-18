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
struct nsm_handle {int /*<<< orphan*/  sm_addrbuf; int /*<<< orphan*/  sm_name; int /*<<< orphan*/  sm_link; int /*<<< orphan*/  sm_count; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nsm_handle*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsm_lock ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void nsm_release(struct nsm_handle *nsm)
{
	if (atomic_dec_and_lock(&nsm->sm_count, &nsm_lock)) {
		list_del(&nsm->sm_link);
		spin_unlock(&nsm_lock);
		dprintk("lockd: destroyed nsm_handle for %s (%s)\n",
				nsm->sm_name, nsm->sm_addrbuf);
		kfree(nsm);
	}
}