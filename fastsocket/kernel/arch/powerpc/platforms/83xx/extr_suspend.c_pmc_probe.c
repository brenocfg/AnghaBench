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
struct resource {int /*<<< orphan*/  start; } ;
struct pmc_type {int /*<<< orphan*/  has_deep_sleep; } ;
struct of_device_id {struct pmc_type* data; } ;
struct of_device {struct device_node* node; } ;
struct mpc83xx_pmc {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ NO_IRQ ; 
 void* clock_regs ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct of_device*) ; 
 int /*<<< orphan*/  get_immrbase () ; 
 int /*<<< orphan*/  has_deep_sleep ; 
 int /*<<< orphan*/  immrbase ; 
 void* ioremap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 scalar_t__ irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_pci_agent ; 
 scalar_t__ mpc83xx_is_pci_agent () ; 
 int /*<<< orphan*/  mpc83xx_set_agent () ; 
 int /*<<< orphan*/  mpc83xx_suspend_ops ; 
 int of_address_to_resource (struct device_node*,int,struct resource*) ; 
 int /*<<< orphan*/  of_device_is_available (struct device_node*) ; 
 struct of_device* pmc_dev ; 
 scalar_t__ pmc_irq ; 
 int /*<<< orphan*/  pmc_irq_handler ; 
 void* pmc_regs ; 
 int request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct of_device*) ; 
 int /*<<< orphan*/  suspend_set_ops (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pmc_probe(struct of_device *ofdev,
                     const struct of_device_id *match)
{
	struct device_node *np = ofdev->node;
	struct resource res;
	struct pmc_type *type = match->data;
	int ret = 0;

	if (!of_device_is_available(np))
		return -ENODEV;

	has_deep_sleep = type->has_deep_sleep;
	immrbase = get_immrbase();
	pmc_dev = ofdev;

	is_pci_agent = mpc83xx_is_pci_agent();
	if (is_pci_agent < 0)
		return is_pci_agent;

	ret = of_address_to_resource(np, 0, &res);
	if (ret)
		return -ENODEV;

	pmc_irq = irq_of_parse_and_map(np, 0);
	if (pmc_irq != NO_IRQ) {
		ret = request_irq(pmc_irq, pmc_irq_handler, IRQF_SHARED,
		                  "pmc", ofdev);

		if (ret)
			return -EBUSY;
	}

	pmc_regs = ioremap(res.start, sizeof(struct mpc83xx_pmc));

	if (!pmc_regs) {
		ret = -ENOMEM;
		goto out;
	}

	ret = of_address_to_resource(np, 1, &res);
	if (ret) {
		ret = -ENODEV;
		goto out_pmc;
	}

	clock_regs = ioremap(res.start, sizeof(struct mpc83xx_pmc));

	if (!clock_regs) {
		ret = -ENOMEM;
		goto out_pmc;
	}

	if (is_pci_agent)
		mpc83xx_set_agent();

	suspend_set_ops(&mpc83xx_suspend_ops);
	return 0;

out_pmc:
	iounmap(pmc_regs);
out:
	if (pmc_irq != NO_IRQ)
		free_irq(pmc_irq, ofdev);

	return ret;
}