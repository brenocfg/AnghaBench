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
struct carm_request {unsigned long long tag; scalar_t__ n_elem; } ;
struct carm_host {unsigned long long msg_alloc; scalar_t__ hw_sg_used; int /*<<< orphan*/  n_msgs; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  assert (int) ; 
 unsigned long long max_queue ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int carm_put_request(struct carm_host *host, struct carm_request *crq)
{
	assert(crq->tag < max_queue);

	if (unlikely((host->msg_alloc & (1ULL << crq->tag)) == 0))
		return -EINVAL; /* tried to clear a tag that was not active */

	assert(host->hw_sg_used >= crq->n_elem);

	host->msg_alloc &= ~(1ULL << crq->tag);
	host->hw_sg_used -= crq->n_elem;
	host->n_msgs--;

	return 0;
}