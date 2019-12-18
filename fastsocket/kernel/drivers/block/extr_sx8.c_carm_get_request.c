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
struct carm_request {int /*<<< orphan*/  sg; scalar_t__ n_elem; int /*<<< orphan*/ * port; } ;
struct carm_host {scalar_t__ hw_sg_used; unsigned long long msg_alloc; scalar_t__ n_msgs; struct carm_request* req; } ;

/* Variables and functions */
 scalar_t__ CARM_MAX_HOST_SG ; 
 scalar_t__ CARM_MAX_REQ ; 
 scalar_t__ CARM_MAX_REQ_SG ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 unsigned int max_queue ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static struct carm_request *carm_get_request(struct carm_host *host)
{
	unsigned int i;

	/* obey global hardware limit on S/G entries */
	if (host->hw_sg_used >= (CARM_MAX_HOST_SG - CARM_MAX_REQ_SG))
		return NULL;

	for (i = 0; i < max_queue; i++)
		if ((host->msg_alloc & (1ULL << i)) == 0) {
			struct carm_request *crq = &host->req[i];
			crq->port = NULL;
			crq->n_elem = 0;

			host->msg_alloc |= (1ULL << i);
			host->n_msgs++;

			assert(host->n_msgs <= CARM_MAX_REQ);
			sg_init_table(crq->sg, CARM_MAX_REQ_SG);
			return crq;
		}

	DPRINTK("no request available, returning NULL\n");
	return NULL;
}