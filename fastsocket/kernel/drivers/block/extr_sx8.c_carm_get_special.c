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
struct request {int dummy; } ;
struct carm_request {struct request* rq; } ;
struct carm_host {int /*<<< orphan*/  lock; int /*<<< orphan*/  oob_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WRITE ; 
 struct request* blk_get_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct carm_request* carm_get_request (struct carm_host*) ; 
 int /*<<< orphan*/  carm_put_request (struct carm_host*,struct carm_request*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct carm_request *carm_get_special(struct carm_host *host)
{
	unsigned long flags;
	struct carm_request *crq = NULL;
	struct request *rq;
	int tries = 5000;

	while (tries-- > 0) {
		spin_lock_irqsave(&host->lock, flags);
		crq = carm_get_request(host);
		spin_unlock_irqrestore(&host->lock, flags);

		if (crq)
			break;
		msleep(10);
	}

	if (!crq)
		return NULL;

	rq = blk_get_request(host->oob_q, WRITE /* bogus */, GFP_KERNEL);
	if (!rq) {
		spin_lock_irqsave(&host->lock, flags);
		carm_put_request(host, crq);
		spin_unlock_irqrestore(&host->lock, flags);
		return NULL;
	}

	crq->rq = rq;
	return crq;
}