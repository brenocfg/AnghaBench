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
struct niu_ldg {int /*<<< orphan*/  irq; } ;
struct niu {int num_ldg; struct niu_ldg* ldg; int /*<<< orphan*/ * irq_name; } ;

/* Variables and functions */
 int IRQF_SAMPLE_RANDOM ; 
 int IRQF_SHARED ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct niu_ldg*) ; 
 int /*<<< orphan*/  niu_interrupt ; 
 int /*<<< orphan*/  niu_set_irq_name (struct niu*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct niu_ldg*) ; 

__attribute__((used)) static int niu_request_irq(struct niu *np)
{
	int i, j, err;

	niu_set_irq_name(np);

	err = 0;
	for (i = 0; i < np->num_ldg; i++) {
		struct niu_ldg *lp = &np->ldg[i];

		err = request_irq(lp->irq, niu_interrupt,
				  IRQF_SHARED | IRQF_SAMPLE_RANDOM,
				  np->irq_name[i], lp);
		if (err)
			goto out_free_irqs;

	}

	return 0;

out_free_irqs:
	for (j = 0; j < i; j++) {
		struct niu_ldg *lp = &np->ldg[j];

		free_irq(lp->irq, lp);
	}
	return err;
}