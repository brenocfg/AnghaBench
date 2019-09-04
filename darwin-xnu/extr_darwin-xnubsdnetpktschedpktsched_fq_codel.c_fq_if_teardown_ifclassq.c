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
struct ifclassq {scalar_t__ ifcq_type; int /*<<< orphan*/ * ifcq_disc; } ;
typedef  int /*<<< orphan*/  fq_if_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (struct ifclassq*) ; 
 scalar_t__ PKTSCHEDT_FQ_CODEL ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  fq_if_destroy (int /*<<< orphan*/ *) ; 
 int ifclassq_detach (struct ifclassq*) ; 

int
fq_if_teardown_ifclassq(struct ifclassq *ifq)
{
	fq_if_t *fqs = (fq_if_t *)ifq->ifcq_disc;

	IFCQ_LOCK_ASSERT_HELD(ifq);
	VERIFY(fqs != NULL && ifq->ifcq_type == PKTSCHEDT_FQ_CODEL);

	fq_if_destroy(fqs);
	ifq->ifcq_disc = NULL;
	return (ifclassq_detach(ifq));
}