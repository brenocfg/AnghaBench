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
struct carm_request {int dummy; } ;
struct carm_host {scalar_t__ n_msgs; scalar_t__ hw_sg_used; } ;

/* Variables and functions */
 scalar_t__ CARM_MSG_LOW_WATER ; 
 scalar_t__ CARM_SG_LOW_WATER ; 
 int /*<<< orphan*/  carm_end_request_queued (struct carm_host*,struct carm_request*,int) ; 
 int /*<<< orphan*/  carm_round_robin (struct carm_host*) ; 
 int max_queue ; 

__attribute__((used)) static inline void carm_end_rq(struct carm_host *host, struct carm_request *crq,
			       int error)
{
	carm_end_request_queued(host, crq, error);
	if (max_queue == 1)
		carm_round_robin(host);
	else if ((host->n_msgs <= CARM_MSG_LOW_WATER) &&
		 (host->hw_sg_used <= CARM_SG_LOW_WATER)) {
		carm_round_robin(host);
	}
}