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
typedef  size_t u_int8_t ;
struct nf_logger {int /*<<< orphan*/ * list; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NFPROTO_NUMPROTO ; 
 size_t NFPROTO_UNSPEC ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_log_mutex ; 
 int /*<<< orphan*/ * nf_loggers ; 
 int /*<<< orphan*/ * nf_loggers_l ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct nf_logger*) ; 
 struct nf_logger* rcu_dereference (int /*<<< orphan*/ ) ; 

int nf_log_register(u_int8_t pf, struct nf_logger *logger)
{
	const struct nf_logger *llog;
	int i;

	if (pf >= ARRAY_SIZE(nf_loggers))
		return -EINVAL;

	for (i = 0; i < ARRAY_SIZE(logger->list); i++)
		INIT_LIST_HEAD(&logger->list[i]);

	mutex_lock(&nf_log_mutex);

	if (pf == NFPROTO_UNSPEC) {
		for (i = NFPROTO_UNSPEC; i < NFPROTO_NUMPROTO; i++)
			list_add_tail(&(logger->list[i]), &(nf_loggers_l[i]));
	} else {
		/* register at end of list to honor first register win */
		list_add_tail(&logger->list[pf], &nf_loggers_l[pf]);
		llog = rcu_dereference(nf_loggers[pf]);
		if (llog == NULL)
			rcu_assign_pointer(nf_loggers[pf], logger);
	}

	mutex_unlock(&nf_log_mutex);

	return 0;
}