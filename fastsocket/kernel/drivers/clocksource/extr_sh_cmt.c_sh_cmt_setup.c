#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sh_timer_config {int clk; int /*<<< orphan*/  clocksource_rating; int /*<<< orphan*/  clockevent_rating; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int flags; struct sh_cmt_priv* dev_id; int /*<<< orphan*/  handler; int /*<<< orphan*/  name; } ;
struct sh_cmt_priv {int width; int overflow_bit; int clear_bits; int /*<<< orphan*/ * mapbase; TYPE_1__ irqaction; int /*<<< orphan*/  clk; struct platform_device* pdev; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_6__ {struct sh_timer_config* platform_data; } ;
struct platform_device {TYPE_3__ dev; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int IRQF_DISABLED ; 
 int IRQF_IRQPOLL ; 
 int IRQF_TIMER ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get (TYPE_3__*,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/ * ioremap_nocache (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct sh_cmt_priv*,int /*<<< orphan*/ ,int) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sh_cmt_priv*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  remove_irq (int,TYPE_1__*) ; 
 int resource_size (struct resource*) ; 
 int setup_irq (int,TYPE_1__*) ; 
 int /*<<< orphan*/  sh_cmt_interrupt ; 
 int sh_cmt_register (struct sh_cmt_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_cmt_setup(struct sh_cmt_priv *p, struct platform_device *pdev)
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
		pr_err("sh_cmt: failed to remap I/O memory\n");
		goto err0;
	}

	/* request irq using setup_irq() (too early for request_irq()) */
	p->irqaction.name = cfg->name;
	p->irqaction.handler = sh_cmt_interrupt;
	p->irqaction.dev_id = p;
	p->irqaction.flags = IRQF_DISABLED | IRQF_TIMER | IRQF_IRQPOLL;
	ret = setup_irq(irq, &p->irqaction);
	if (ret) {
		pr_err("sh_cmt: failed to request irq %d\n", irq);
		goto err1;
	}

	/* get hold of clock */
	p->clk = clk_get(&p->pdev->dev, cfg->clk);
	if (IS_ERR(p->clk)) {
		pr_err("sh_cmt: cannot get clock \"%s\"\n", cfg->clk);
		ret = PTR_ERR(p->clk);
		goto err2;
	}

	if (resource_size(res) == 6) {
		p->width = 16;
		p->overflow_bit = 0x80;
		p->clear_bits = ~0x80;
	} else {
		p->width = 32;
		p->overflow_bit = 0x8000;
		p->clear_bits = ~0xc000;
	}

	return sh_cmt_register(p, cfg->name,
			       cfg->clockevent_rating,
			       cfg->clocksource_rating);
 err2:
	remove_irq(irq, &p->irqaction);
 err1:
	iounmap(p->mapbase);
 err0:
	return ret;
}