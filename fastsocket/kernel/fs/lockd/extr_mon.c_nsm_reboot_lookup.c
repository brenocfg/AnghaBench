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
struct nsm_handle {int /*<<< orphan*/  sm_count; int /*<<< orphan*/  sm_addrbuf; int /*<<< orphan*/  sm_name; scalar_t__ sm_monitored; } ;
struct nlm_reboot {int /*<<< orphan*/  mon; int /*<<< orphan*/  len; int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  nsm_lock ; 
 struct nsm_handle* nsm_lookup_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

struct nsm_handle *nsm_reboot_lookup(const struct nlm_reboot *info)
{
	struct nsm_handle *cached;

	spin_lock(&nsm_lock);

	cached = nsm_lookup_priv(&info->priv);
	if (unlikely(cached == NULL)) {
		spin_unlock(&nsm_lock);
		dprintk("lockd: never saw rebooted peer '%.*s' before\n",
				info->len, info->mon);
		return cached;
	}

	atomic_inc(&cached->sm_count);
	spin_unlock(&nsm_lock);

	/*
	 * During subsequent lock activity, force a fresh
	 * notification to be set up for this host.
	 */
	cached->sm_monitored = 0;

	dprintk("lockd: host %s (%s) rebooted, cnt %d\n",
			cached->sm_name, cached->sm_addrbuf,
			atomic_read(&cached->sm_count));
	return cached;
}