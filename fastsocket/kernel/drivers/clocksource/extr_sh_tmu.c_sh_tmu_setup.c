#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int irq; int flags; struct sh_tmu_priv* dev_id; int /*<<< orphan*/  handler; int /*<<< orphan*/  name; } ;
struct sh_tmu_priv {int /*<<< orphan*/ * mapbase; int /*<<< orphan*/  clk; struct platform_device* pdev; TYPE_1__ irqaction; } ;
struct sh_timer_config {int /*<<< orphan*/  clocksource_rating; int /*<<< orphan*/  clockevent_rating; int /*<<< orphan*/  name; int /*<<< orphan*/  clk; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_5__ {struct sh_timer_config* platform_data; } ;
struct platform_device {TYPE_2__ dev; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int IRQF_DISABLED ; 
 int IRQF_IRQPOLL ; 
 int IRQF_TIMER ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/ * ioremap_nocache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct sh_tmu_priv*,int /*<<< orphan*/ ,int) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sh_tmu_priv*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  sh_tmu_interrupt ; 
 int sh_tmu_register (struct sh_tmu_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_tmu_setup(struct sh_tmu_priv *p, struct platform_device *pdev)
{
	struct sh_timer_config *cfg = pdev->dev.platform_data;
	struct resource *res;
	int irq, ret;
	ret = -ENXIO;

	memset(p, 0, sizeof(*p));
	p->pdev = pdev;

	if (!cfg) {
		dev_err(&p->pdev->dev, "missing platform data\n");
		goto err0;
	}

	platform_set_drvdata(pdev, p);

	res = platform_get_resource(p->pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&p->pdev->dev, "failed to get I/O memory\n");
		goto err0;
	}

	irq = platform_get_irq(p->pdev, 0);
	if (irq < 0) {
		dev_err(&p->pdev->dev, "failed to get irq\n");
		goto err0;
	}

	/* map memory, let mapbase point to our channel */
	p->mapbase = ioremap_nocache(res->start, resource_size(res));
	if (p->mapbase == NULL) {
		pr_err("sh_tmu: failed to remap I/O memory\n");
		goto err0;
	}

	/* setup data for setup_irq() (too early for request_irq()) */
	p->irqaction.name = cfg->name;
	p->irqaction.handler = sh_tmu_interrupt;
	p->irqaction.dev_id = p;
	p->irqaction.irq = irq;
	p->irqaction.flags = IRQF_DISABLED | IRQF_TIMER | IRQF_IRQPOLL;

	/* get hold of clock */
	p->clk = clk_get(&p->pdev->dev, cfg->clk);
	if (IS_ERR(p->clk)) {
		pr_err("sh_tmu: cannot get clock \"%s\"\n", cfg->clk);
		ret = PTR_ERR(p->clk);
		goto err1;
	}

	return sh_tmu_register(p, cfg->name,
			       cfg->clockevent_rating,
			       cfg->clocksource_rating);
 err1:
	iounmap(p->mapbase);
 err0:
	return ret;
}