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
struct ip_vs_service_user_kern {scalar_t__ af; int netmask; int flags; int timeout; scalar_t__* pe_name; scalar_t__* sched_name; } ;
struct ip_vs_service {int flags; int timeout; int netmask; struct ip_vs_pe* pe; struct ip_vs_scheduler* scheduler; int /*<<< orphan*/  usecnt; } ;
struct ip_vs_scheduler {int dummy; } ;
struct ip_vs_pe {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int EINVAL ; 
 int ENOENT ; 
 int HZ ; 
 int IP_VS_SVC_F_HASHED ; 
 int /*<<< orphan*/  IP_VS_WAIT_WHILE (int) ; 
 int /*<<< orphan*/  __ip_vs_svc_lock ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_vs_bind_pe (struct ip_vs_service*,struct ip_vs_pe*) ; 
 int ip_vs_bind_scheduler (struct ip_vs_service*,struct ip_vs_scheduler*) ; 
 struct ip_vs_pe* ip_vs_pe_getbyname (scalar_t__*) ; 
 int /*<<< orphan*/  ip_vs_pe_put (struct ip_vs_pe*) ; 
 struct ip_vs_scheduler* ip_vs_scheduler_get (scalar_t__*) ; 
 int /*<<< orphan*/  ip_vs_scheduler_put (struct ip_vs_scheduler*) ; 
 int /*<<< orphan*/  ip_vs_unbind_pe (struct ip_vs_service*) ; 
 int ip_vs_unbind_scheduler (struct ip_vs_service*) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ip_vs_edit_service(struct ip_vs_service *svc, struct ip_vs_service_user_kern *u)
{
	struct ip_vs_scheduler *sched, *old_sched;
	struct ip_vs_pe *pe = NULL, *old_pe = NULL;
	int ret = 0;

	/*
	 * Lookup the scheduler, by 'u->sched_name'
	 */
	sched = ip_vs_scheduler_get(u->sched_name);
	if (sched == NULL) {
		pr_info("Scheduler module ip_vs_%s not found\n", u->sched_name);
		return -ENOENT;
	}
	old_sched = sched;

	if (u->pe_name && *u->pe_name) {
		pe = ip_vs_pe_getbyname(u->pe_name);
		if (pe == NULL) {
			pr_info("persistence engine module ip_vs_pe_%s "
				"not found\n", u->pe_name);
			ret = -ENOENT;
			goto out;
		}
		old_pe = pe;
	}

#ifdef CONFIG_IP_VS_IPV6
	if (u->af == AF_INET6 && (u->netmask < 1 || u->netmask > 128)) {
		ret = -EINVAL;
		goto out;
	}
#endif

	write_lock_bh(&__ip_vs_svc_lock);

	/*
	 * Wait until all other svc users go away.
	 */
	IP_VS_WAIT_WHILE(atomic_read(&svc->usecnt) > 1);

	/*
	 * Set the flags and timeout value
	 */
	svc->flags = u->flags | IP_VS_SVC_F_HASHED;
	svc->timeout = u->timeout * HZ;
	svc->netmask = u->netmask;

	old_sched = svc->scheduler;
	if (sched != old_sched) {
		/*
		 * Unbind the old scheduler
		 */
		if ((ret = ip_vs_unbind_scheduler(svc))) {
			old_sched = sched;
			goto out_unlock;
		}

		/*
		 * Bind the new scheduler
		 */
		if ((ret = ip_vs_bind_scheduler(svc, sched))) {
			/*
			 * If ip_vs_bind_scheduler fails, restore the old
			 * scheduler.
			 * The main reason of failure is out of memory.
			 *
			 * The question is if the old scheduler can be
			 * restored all the time. TODO: if it cannot be
			 * restored some time, we must delete the service,
			 * otherwise the system may crash.
			 */
			ip_vs_bind_scheduler(svc, old_sched);
			old_sched = sched;
			goto out_unlock;
		}
	}

	old_pe = svc->pe;
	if (pe != old_pe) {
		ip_vs_unbind_pe(svc);
		ip_vs_bind_pe(svc, pe);
	}

  out_unlock:
	write_unlock_bh(&__ip_vs_svc_lock);
  out:
	ip_vs_scheduler_put(old_sched);
	ip_vs_pe_put(old_pe);
	return ret;
}