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
struct enic {unsigned int wq_count; unsigned int rq_count; unsigned int cq_count; unsigned int intr_count; int /*<<< orphan*/ * intr; int /*<<< orphan*/ * cq; int /*<<< orphan*/ * rq; int /*<<< orphan*/ * wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  vnic_cq_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_intr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_rq_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_wq_free (int /*<<< orphan*/ *) ; 

void enic_free_vnic_resources(struct enic *enic)
{
	unsigned int i;

	for (i = 0; i < enic->wq_count; i++)
		vnic_wq_free(&enic->wq[i]);
	for (i = 0; i < enic->rq_count; i++)
		vnic_rq_free(&enic->rq[i]);
	for (i = 0; i < enic->cq_count; i++)
		vnic_cq_free(&enic->cq[i]);
	for (i = 0; i < enic->intr_count; i++)
		vnic_intr_free(&enic->intr[i]);
}