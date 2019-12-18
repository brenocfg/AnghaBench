#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tmio_nand_data {int num_partitions; struct mtd_partition* partition; int /*<<< orphan*/  badblock_pattern; } ;
struct TYPE_5__ {int size; int bytes; int /*<<< orphan*/  correct; int /*<<< orphan*/  calculate; int /*<<< orphan*/  hwctl; int /*<<< orphan*/  mode; } ;
struct nand_chip {int chip_delay; int /*<<< orphan*/  waitfunc; int /*<<< orphan*/  badblock_pattern; TYPE_1__ ecc; int /*<<< orphan*/  verify_buf; int /*<<< orphan*/  read_buf; int /*<<< orphan*/  write_buf; int /*<<< orphan*/  read_byte; int /*<<< orphan*/  dev_ready; int /*<<< orphan*/  cmd_ctrl; void* IO_ADDR_W; void* IO_ADDR_R; } ;
struct mtd_info {char* name; struct nand_chip* priv; } ;
struct tmio_nand {int fcr_base; int irq; void* ccr; void* fcr; struct nand_chip chip; struct mtd_info mtd; struct platform_device* dev; } ;
struct resource {int start; int end; } ;
struct TYPE_6__ {scalar_t__ platform_data; } ;
struct platform_device {TYPE_2__ dev; } ;
struct mtd_partition {int dummy; } ;
struct mfd_cell {struct tmio_nand_data* driver_data; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_DISABLED ; 
 int /*<<< orphan*/  NAND_ECC_HW ; 
 int add_mtd_device (struct mtd_info*) ; 
 int add_mtd_partitions (struct mtd_info*,struct mtd_partition*,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  free_irq (int,struct tmio_nand*) ; 
 void* ioremap (int,int) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 int /*<<< orphan*/  kfree (struct tmio_nand*) ; 
 struct tmio_nand* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_release (struct mtd_info*) ; 
 scalar_t__ nand_scan (struct mtd_info*,int) ; 
 int parse_mtd_partitions (struct mtd_info*,int /*<<< orphan*/ ,struct mtd_partition**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  part_probes ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tmio_nand*) ; 
 int request_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tmio_nand*) ; 
 int tmio_hw_init (struct platform_device*,struct tmio_nand*) ; 
 int /*<<< orphan*/  tmio_hw_stop (struct platform_device*,struct tmio_nand*) ; 
 int /*<<< orphan*/  tmio_irq ; 
 int /*<<< orphan*/  tmio_nand_calculate_ecc ; 
 int /*<<< orphan*/  tmio_nand_correct_data ; 
 int /*<<< orphan*/  tmio_nand_dev_ready ; 
 int /*<<< orphan*/  tmio_nand_enable_hwecc ; 
 int /*<<< orphan*/  tmio_nand_hwcontrol ; 
 int /*<<< orphan*/  tmio_nand_read_buf ; 
 int /*<<< orphan*/  tmio_nand_read_byte ; 
 int /*<<< orphan*/  tmio_nand_verify_buf ; 
 int /*<<< orphan*/  tmio_nand_wait ; 
 int /*<<< orphan*/  tmio_nand_write_buf ; 

__attribute__((used)) static int tmio_probe(struct platform_device *dev)
{
	struct mfd_cell *cell = (struct mfd_cell *)dev->dev.platform_data;
	struct tmio_nand_data *data = cell->driver_data;
	struct resource *fcr = platform_get_resource(dev,
			IORESOURCE_MEM, 0);
	struct resource *ccr = platform_get_resource(dev,
			IORESOURCE_MEM, 1);
	int irq = platform_get_irq(dev, 0);
	struct tmio_nand *tmio;
	struct mtd_info *mtd;
	struct nand_chip *nand_chip;
#ifdef CONFIG_MTD_PARTITIONS
	struct mtd_partition *parts;
	int nbparts = 0;
#endif
	int retval;

	if (data == NULL)
		dev_warn(&dev->dev, "NULL platform data!\n");

	tmio = kzalloc(sizeof *tmio, GFP_KERNEL);
	if (!tmio) {
		retval = -ENOMEM;
		goto err_kzalloc;
	}

	tmio->dev = dev;

	platform_set_drvdata(dev, tmio);
	mtd = &tmio->mtd;
	nand_chip = &tmio->chip;
	mtd->priv = nand_chip;
	mtd->name = "tmio-nand";

	tmio->ccr = ioremap(ccr->start, ccr->end - ccr->start + 1);
	if (!tmio->ccr) {
		retval = -EIO;
		goto err_iomap_ccr;
	}

	tmio->fcr_base = fcr->start & 0xfffff;
	tmio->fcr = ioremap(fcr->start, fcr->end - fcr->start + 1);
	if (!tmio->fcr) {
		retval = -EIO;
		goto err_iomap_fcr;
	}

	retval = tmio_hw_init(dev, tmio);
	if (retval)
		goto err_hwinit;

	/* Set address of NAND IO lines */
	nand_chip->IO_ADDR_R = tmio->fcr;
	nand_chip->IO_ADDR_W = tmio->fcr;

	/* Set address of hardware control function */
	nand_chip->cmd_ctrl = tmio_nand_hwcontrol;
	nand_chip->dev_ready = tmio_nand_dev_ready;
	nand_chip->read_byte = tmio_nand_read_byte;
	nand_chip->write_buf = tmio_nand_write_buf;
	nand_chip->read_buf = tmio_nand_read_buf;
	nand_chip->verify_buf = tmio_nand_verify_buf;

	/* set eccmode using hardware ECC */
	nand_chip->ecc.mode = NAND_ECC_HW;
	nand_chip->ecc.size = 512;
	nand_chip->ecc.bytes = 6;
	nand_chip->ecc.hwctl = tmio_nand_enable_hwecc;
	nand_chip->ecc.calculate = tmio_nand_calculate_ecc;
	nand_chip->ecc.correct = tmio_nand_correct_data;

	if (data)
		nand_chip->badblock_pattern = data->badblock_pattern;

	/* 15 us command delay time */
	nand_chip->chip_delay = 15;

	retval = request_irq(irq, &tmio_irq,
				IRQF_DISABLED, dev_name(&dev->dev), tmio);
	if (retval) {
		dev_err(&dev->dev, "request_irq error %d\n", retval);
		goto err_irq;
	}

	tmio->irq = irq;
	nand_chip->waitfunc = tmio_nand_wait;

	/* Scan to find existence of the device */
	if (nand_scan(mtd, 1)) {
		retval = -ENODEV;
		goto err_scan;
	}
	/* Register the partitions */
#ifdef CONFIG_MTD_PARTITIONS
#ifdef CONFIG_MTD_CMDLINE_PARTS
	nbparts = parse_mtd_partitions(mtd, part_probes, &parts, 0);
#endif
	if (nbparts <= 0 && data) {
		parts = data->partition;
		nbparts = data->num_partitions;
	}

	if (nbparts)
		retval = add_mtd_partitions(mtd, parts, nbparts);
	else
#endif
	retval = add_mtd_device(mtd);

	if (!retval)
		return retval;

	nand_release(mtd);

err_scan:
	if (tmio->irq)
		free_irq(tmio->irq, tmio);
err_irq:
	tmio_hw_stop(dev, tmio);
err_hwinit:
	iounmap(tmio->fcr);
err_iomap_fcr:
	iounmap(tmio->ccr);
err_iomap_ccr:
	kfree(tmio);
err_kzalloc:
	return retval;
}