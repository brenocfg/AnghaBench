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
 int IPMI_SET_TIMEOUT_FORCE_HB ; 
 int IPMI_SET_TIMEOUT_HB_IF_NECESSARY ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int i_ipmi_set_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int ipmi_heartbeat () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_timeout_lock ; 
 int /*<<< orphan*/  set_timeout_recv_msg ; 
 int /*<<< orphan*/  set_timeout_smi_msg ; 
 int /*<<< orphan*/  set_timeout_tofree ; 
 int /*<<< orphan*/  set_timeout_wait ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipmi_set_timeout(int do_heartbeat)
{
	int send_heartbeat_now;
	int rv;


	/* We can only send one of these at a time. */
	mutex_lock(&set_timeout_lock);

	atomic_set(&set_timeout_tofree, 2);

	rv = i_ipmi_set_timeout(&set_timeout_smi_msg,
				&set_timeout_recv_msg,
				&send_heartbeat_now);
	if (rv) {
		mutex_unlock(&set_timeout_lock);
		goto out;
	}

	wait_for_completion(&set_timeout_wait);

	mutex_unlock(&set_timeout_lock);

	if ((do_heartbeat == IPMI_SET_TIMEOUT_FORCE_HB)
	    || ((send_heartbeat_now)
		&& (do_heartbeat == IPMI_SET_TIMEOUT_HB_IF_NECESSARY)))
		rv = ipmi_heartbeat();

out:
	return rv;
}