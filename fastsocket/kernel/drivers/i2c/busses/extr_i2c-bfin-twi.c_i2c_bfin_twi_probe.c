#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {size_t id; int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct i2c_adapter {size_t nr; int class; TYPE_1__ dev; struct bfin_twi_iface* algo_data; int /*<<< orphan*/ * algo; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct bfin_twi_iface {scalar_t__ irq; int /*<<< orphan*/ * regs_base; struct i2c_adapter adap; TYPE_2__ timeout_timer; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int CONFIG_I2C_BLACKFIN_TWI_CLK_KHZ ; 
 int ENODEV ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_CLASS_HWMON ; 
 int I2C_CLASS_SPD ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_DISABLED ; 
 int /*<<< orphan*/  SSYNC () ; 
 int TWI_ENA ; 
 int /*<<< orphan*/  bfin_twi_algorithm ; 
 int /*<<< orphan*/  bfin_twi_interrupt_entry ; 
 int /*<<< orphan*/  bfin_twi_timeout ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct bfin_twi_iface*) ; 
 int get_sclk () ; 
 int i2c_add_numbered_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  init_timer (TYPE_2__*) ; 
 int /*<<< orphan*/ * ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct bfin_twi_iface*) ; 
 struct bfin_twi_iface* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  peripheral_free_list (int /*<<< orphan*/ ) ; 
 int peripheral_request_list (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * pin_req ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct bfin_twi_iface*) ; 
 int read_CONTROL (struct bfin_twi_iface*) ; 
 int request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bfin_twi_iface*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_CLKDIV (struct bfin_twi_iface*,unsigned int) ; 
 int /*<<< orphan*/  write_CONTROL (struct bfin_twi_iface*,int) ; 

__attribute__((used)) static int i2c_bfin_twi_probe(struct platform_device *pdev)
{
	struct bfin_twi_iface *iface;
	struct i2c_adapter *p_adap;
	struct resource *res;
	int rc;
	unsigned int clkhilow;

	iface = kzalloc(sizeof(struct bfin_twi_iface), GFP_KERNEL);
	if (!iface) {
		dev_err(&pdev->dev, "Cannot allocate memory\n");
		rc = -ENOMEM;
		goto out_error_nomem;
	}

	spin_lock_init(&(iface->lock));

	/* Find and map our resources */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res == NULL) {
		dev_err(&pdev->dev, "Cannot get IORESOURCE_MEM\n");
		rc = -ENOENT;
		goto out_error_get_res;
	}

	iface->regs_base = ioremap(res->start, resource_size(res));
	if (iface->regs_base == NULL) {
		dev_err(&pdev->dev, "Cannot map IO\n");
		rc = -ENXIO;
		goto out_error_ioremap;
	}

	iface->irq = platform_get_irq(pdev, 0);
	if (iface->irq < 0) {
		dev_err(&pdev->dev, "No IRQ specified\n");
		rc = -ENOENT;
		goto out_error_no_irq;
	}

	init_timer(&(iface->timeout_timer));
	iface->timeout_timer.function = bfin_twi_timeout;
	iface->timeout_timer.data = (unsigned long)iface;

	p_adap = &iface->adap;
	p_adap->nr = pdev->id;
	strlcpy(p_adap->name, pdev->name, sizeof(p_adap->name));
	p_adap->algo = &bfin_twi_algorithm;
	p_adap->algo_data = iface;
	p_adap->class = I2C_CLASS_HWMON | I2C_CLASS_SPD;
	p_adap->dev.parent = &pdev->dev;

	rc = peripheral_request_list(pin_req[pdev->id], "i2c-bfin-twi");
	if (rc) {
		dev_err(&pdev->dev, "Can't setup pin mux!\n");
		goto out_error_pin_mux;
	}

	rc = request_irq(iface->irq, bfin_twi_interrupt_entry,
		IRQF_DISABLED, pdev->name, iface);
	if (rc) {
		dev_err(&pdev->dev, "Can't get IRQ %d !\n", iface->irq);
		rc = -ENODEV;
		goto out_error_req_irq;
	}

	/* Set TWI internal clock as 10MHz */
	write_CONTROL(iface, ((get_sclk() / 1024 / 1024 + 5) / 10) & 0x7F);

	/*
	 * We will not end up with a CLKDIV=0 because no one will specify
	 * 20kHz SCL or less in Kconfig now. (5 * 1024 / 20 = 0x100)
	 */
	clkhilow = 5 * 1024 / CONFIG_I2C_BLACKFIN_TWI_CLK_KHZ;

	/* Set Twi interface clock as specified */
	write_CLKDIV(iface, (clkhilow << 8) | clkhilow);

	/* Enable TWI */
	write_CONTROL(iface, read_CONTROL(iface) | TWI_ENA);
	SSYNC();

	rc = i2c_add_numbered_adapter(p_adap);
	if (rc < 0) {
		dev_err(&pdev->dev, "Can't add i2c adapter!\n");
		goto out_error_add_adapter;
	}

	platform_set_drvdata(pdev, iface);

	dev_info(&pdev->dev, "Blackfin BF5xx on-chip I2C TWI Contoller, "
		"regs_base@%p\n", iface->regs_base);

	return 0;

out_error_add_adapter:
	free_irq(iface->irq, iface);
out_error_req_irq:
out_error_no_irq:
	peripheral_free_list(pin_req[pdev->id]);
out_error_pin_mux:
	iounmap(iface->regs_base);
out_error_ioremap:
out_error_get_res:
	kfree(iface);
out_error_nomem:
	return rc;
}