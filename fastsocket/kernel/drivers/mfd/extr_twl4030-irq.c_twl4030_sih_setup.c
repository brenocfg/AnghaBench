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
struct sih_agent {unsigned int irq_base; int /*<<< orphan*/  edge_work; int /*<<< orphan*/  mask_work; int /*<<< orphan*/  imr; struct sih const* sih; } ;
struct sih {int module; unsigned int bits; int /*<<< orphan*/  name; scalar_t__ set_cor; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct sih*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int NR_IRQS ; 
 int /*<<< orphan*/  WARN (int,char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  activate_irq (int) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_twl4030_sih ; 
 struct sih_agent* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int,unsigned int,int) ; 
 int /*<<< orphan*/  set_irq_chained_handler (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_irq_chip_and_handler (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_irq_chip_data (int,struct sih_agent*) ; 
 int /*<<< orphan*/  set_irq_data (int,struct sih_agent*) ; 
 struct sih* sih_modules ; 
 int twl4030_irq_base ; 
 int twl4030_irq_next ; 
 int /*<<< orphan*/  twl4030_sih_do_edge ; 
 int /*<<< orphan*/  twl4030_sih_do_mask ; 
 int /*<<< orphan*/  twl4030_sih_irq_chip ; 

int twl4030_sih_setup(int module)
{
	int			sih_mod;
	const struct sih	*sih = NULL;
	struct sih_agent	*agent;
	int			i, irq;
	int			status = -EINVAL;
	unsigned		irq_base = twl4030_irq_next;

	/* only support modules with standard clear-on-read for now */
	for (sih_mod = 0, sih = sih_modules;
			sih_mod < ARRAY_SIZE(sih_modules);
			sih_mod++, sih++) {
		if (sih->module == module && sih->set_cor) {
			if (!WARN((irq_base + sih->bits) > NR_IRQS,
					"irq %d for %s too big\n",
					irq_base + sih->bits,
					sih->name))
				status = 0;
			break;
		}
	}
	if (status < 0)
		return status;

	agent = kzalloc(sizeof *agent, GFP_KERNEL);
	if (!agent)
		return -ENOMEM;

	status = 0;

	agent->irq_base = irq_base;
	agent->sih = sih;
	agent->imr = ~0;
	INIT_WORK(&agent->mask_work, twl4030_sih_do_mask);
	INIT_WORK(&agent->edge_work, twl4030_sih_do_edge);

	for (i = 0; i < sih->bits; i++) {
		irq = irq_base + i;

		set_irq_chip_and_handler(irq, &twl4030_sih_irq_chip,
				handle_edge_irq);
		set_irq_chip_data(irq, agent);
		activate_irq(irq);
	}

	status = irq_base;
	twl4030_irq_next += i;

	/* replace generic PIH handler (handle_simple_irq) */
	irq = sih_mod + twl4030_irq_base;
	set_irq_data(irq, agent);
	set_irq_chained_handler(irq, handle_twl4030_sih);

	pr_info("twl4030: %s (irq %d) chaining IRQs %d..%d\n", sih->name,
			irq, irq_base, twl4030_irq_next - 1);

	return status;
}