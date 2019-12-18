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
struct nf_queue_handler {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct nf_queue_handler const**) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nf_queue_handler const** queue_handler ; 
 int /*<<< orphan*/  queue_handler_mutex ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct nf_queue_handler const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void nf_unregister_queue_handlers(const struct nf_queue_handler *qh)
{
	u_int8_t pf;

	mutex_lock(&queue_handler_mutex);
	for (pf = 0; pf < ARRAY_SIZE(queue_handler); pf++)  {
		if (queue_handler[pf] == qh)
			rcu_assign_pointer(queue_handler[pf], NULL);
	}
	mutex_unlock(&queue_handler_mutex);

	synchronize_rcu();
}