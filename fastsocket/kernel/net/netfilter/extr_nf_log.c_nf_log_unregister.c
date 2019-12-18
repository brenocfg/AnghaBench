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
typedef  struct nf_logger {int /*<<< orphan*/ * list; } const nf_logger ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_log_mutex ; 
 int /*<<< orphan*/ * nf_loggers ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nf_logger const* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void nf_log_unregister(struct nf_logger *logger)
{
	const struct nf_logger *c_logger;
	int i;

	mutex_lock(&nf_log_mutex);
	for (i = 0; i < ARRAY_SIZE(nf_loggers); i++) {
		c_logger = rcu_dereference(nf_loggers[i]);
		if (c_logger == logger)
			rcu_assign_pointer(nf_loggers[i], NULL);
		list_del(&logger->list[i]);
	}
	mutex_unlock(&nf_log_mutex);

	synchronize_rcu();
}