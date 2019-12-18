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
struct cfq_queue {int dummy; } ;

/* Variables and functions */
 int ELV_MQUEUE_MAY ; 
 int ELV_MQUEUE_MUST ; 
 int /*<<< orphan*/  cfq_cfqq_must_alloc_slice (struct cfq_queue*) ; 
 scalar_t__ cfq_cfqq_wait_request (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_mark_cfqq_must_alloc_slice (struct cfq_queue*) ; 

__attribute__((used)) static inline int __cfq_may_queue(struct cfq_queue *cfqq)
{
	if (cfq_cfqq_wait_request(cfqq) && !cfq_cfqq_must_alloc_slice(cfqq)) {
		cfq_mark_cfqq_must_alloc_slice(cfqq);
		return ELV_MQUEUE_MUST;
	}

	return ELV_MQUEUE_MAY;
}