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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blocking_notifier_chain_unregister (int /*<<< orphan*/ *,struct notifier_block*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ wf_client_count ; 
 int /*<<< orphan*/  wf_client_list ; 
 int /*<<< orphan*/  wf_lock ; 
 int /*<<< orphan*/  wf_stop_thread () ; 

int wf_unregister_client(struct notifier_block *nb)
{
	mutex_lock(&wf_lock);
	blocking_notifier_chain_unregister(&wf_client_list, nb);
	wf_client_count++;
	if (wf_client_count == 0)
		wf_stop_thread();
	mutex_unlock(&wf_lock);

	return 0;
}