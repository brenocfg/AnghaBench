#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  fq_mbufq; scalar_t__ fq_ptype; } ;
typedef  TYPE_1__ fq_t ;
typedef  scalar_t__ classq_pkt_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  MBUFQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MCR_SLEEP ; 
 scalar_t__ QP_MBUF ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flowq_cache ; 
 int /*<<< orphan*/  flowq_size ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* mcache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

fq_t *
fq_alloc(classq_pkt_type_t ptype)
{
	fq_t *fq = NULL;
	fq = mcache_alloc(flowq_cache, MCR_SLEEP);
	if (fq == NULL) {
		log(LOG_ERR, "%s: unable to allocate from flowq_cache\n");
		return (NULL);
	}

	bzero(fq, flowq_size);
	fq->fq_ptype = ptype;
	if (ptype == QP_MBUF) {
		MBUFQ_INIT(&fq->fq_mbufq);
	}
	return (fq);
}