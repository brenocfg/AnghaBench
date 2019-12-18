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
struct slib {int dummy; } ;
struct qdio_q {struct slib* slib; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON (unsigned long) ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 struct qdio_q* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct qdio_q*) ; 
 int /*<<< orphan*/  qdio_q_cache ; 

__attribute__((used)) static int __qdio_allocate_qs(struct qdio_q **irq_ptr_qs, int nr_queues)
{
	struct qdio_q *q;
	int i;

	for (i = 0; i < nr_queues; i++) {
		q = kmem_cache_alloc(qdio_q_cache, GFP_KERNEL);
		if (!q)
			return -ENOMEM;
		WARN_ON((unsigned long)q & 0xff);

		q->slib = (struct slib *) __get_free_page(GFP_KERNEL);
		if (!q->slib) {
			kmem_cache_free(qdio_q_cache, q);
			return -ENOMEM;
		}
		WARN_ON((unsigned long)q->slib & 0x7ff);
		irq_ptr_qs[i] = q;
	}
	return 0;
}