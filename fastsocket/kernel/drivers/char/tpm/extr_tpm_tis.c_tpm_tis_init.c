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
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {unsigned int irq; scalar_t__ iobase; int /*<<< orphan*/  list; int /*<<< orphan*/  locality; TYPE_1__ miscdev; int /*<<< orphan*/  int_queue; int /*<<< orphan*/  read_queue; void* timeout_d; void* timeout_c; void* timeout_b; void* timeout_a; } ;
struct tpm_chip {int /*<<< orphan*/  dev; TYPE_2__ vendor; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  TIS_LONG_TIMEOUT ; 
 int /*<<< orphan*/  TIS_SHORT_TIMEOUT ; 
 scalar_t__ TPM_DID_VID (int /*<<< orphan*/ ) ; 
 int TPM_GLOBAL_INT_ENABLE ; 
 int TPM_INTF_BURST_COUNT_STATIC ; 
 scalar_t__ TPM_INTF_CAPS (int /*<<< orphan*/ ) ; 
 int TPM_INTF_CMD_READY_INT ; 
 int TPM_INTF_DATA_AVAIL_INT ; 
 int TPM_INTF_INT_EDGE_FALLING ; 
 int TPM_INTF_INT_EDGE_RISING ; 
 int TPM_INTF_INT_LEVEL_HIGH ; 
 int TPM_INTF_INT_LEVEL_LOW ; 
 int TPM_INTF_LOCALITY_CHANGE_INT ; 
 int TPM_INTF_STS_VALID_INT ; 
 scalar_t__ TPM_INT_ENABLE (int /*<<< orphan*/ ) ; 
 scalar_t__ TPM_INT_STATUS (int /*<<< orphan*/ ) ; 
 scalar_t__ TPM_INT_VECTOR (int /*<<< orphan*/ ) ; 
 scalar_t__ TPM_RID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free_irq (int,struct tpm_chip*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 scalar_t__ interrupts ; 
 int ioread32 (scalar_t__) ; 
 unsigned int ioread8 (scalar_t__) ; 
 scalar_t__ ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  iowrite8 (int,scalar_t__) ; 
 scalar_t__ itpm ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tpm_chip*) ; 
 scalar_t__ request_locality (struct tpm_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tis_chips ; 
 int /*<<< orphan*/  tis_int_handler ; 
 int /*<<< orphan*/  tis_int_probe ; 
 int /*<<< orphan*/  tis_lock ; 
 int /*<<< orphan*/  tpm_continue_selftest (struct tpm_chip*) ; 
 int /*<<< orphan*/  tpm_gen_interrupt (struct tpm_chip*) ; 
 int /*<<< orphan*/  tpm_get_timeouts (struct tpm_chip*) ; 
 struct tpm_chip* tpm_register_hardware (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tpm_remove_hardware (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpm_tis ; 

__attribute__((used)) static int tpm_tis_init(struct device *dev, resource_size_t start,
			resource_size_t len, unsigned int irq)
{
	u32 vendor, intfcaps, intmask;
	int rc, i;
	struct tpm_chip *chip;

	if (!(chip = tpm_register_hardware(dev, &tpm_tis)))
		return -ENODEV;

	chip->vendor.iobase = ioremap(start, len);
	if (!chip->vendor.iobase) {
		rc = -EIO;
		goto out_err;
	}

	/* Default timeouts */
	chip->vendor.timeout_a = msecs_to_jiffies(TIS_SHORT_TIMEOUT);
	chip->vendor.timeout_b = msecs_to_jiffies(TIS_LONG_TIMEOUT);
	chip->vendor.timeout_c = msecs_to_jiffies(TIS_SHORT_TIMEOUT);
	chip->vendor.timeout_d = msecs_to_jiffies(TIS_SHORT_TIMEOUT);

	if (request_locality(chip, 0) != 0) {
		rc = -ENODEV;
		goto out_err;
	}

	vendor = ioread32(chip->vendor.iobase + TPM_DID_VID(0));

	dev_info(dev,
		 "1.2 TPM (device-id 0x%X, rev-id %d)\n",
		 vendor >> 16, ioread8(chip->vendor.iobase + TPM_RID(0)));

	if (itpm)
		dev_info(dev, "Intel iTPM workaround enabled\n");


	/* Figure out the capabilities */
	intfcaps =
	    ioread32(chip->vendor.iobase +
		     TPM_INTF_CAPS(chip->vendor.locality));
	dev_dbg(dev, "TPM interface capabilities (0x%x):\n",
		intfcaps);
	if (intfcaps & TPM_INTF_BURST_COUNT_STATIC)
		dev_dbg(dev, "\tBurst Count Static\n");
	if (intfcaps & TPM_INTF_CMD_READY_INT)
		dev_dbg(dev, "\tCommand Ready Int Support\n");
	if (intfcaps & TPM_INTF_INT_EDGE_FALLING)
		dev_dbg(dev, "\tInterrupt Edge Falling\n");
	if (intfcaps & TPM_INTF_INT_EDGE_RISING)
		dev_dbg(dev, "\tInterrupt Edge Rising\n");
	if (intfcaps & TPM_INTF_INT_LEVEL_LOW)
		dev_dbg(dev, "\tInterrupt Level Low\n");
	if (intfcaps & TPM_INTF_INT_LEVEL_HIGH)
		dev_dbg(dev, "\tInterrupt Level High\n");
	if (intfcaps & TPM_INTF_LOCALITY_CHANGE_INT)
		dev_dbg(dev, "\tLocality Change Int Support\n");
	if (intfcaps & TPM_INTF_STS_VALID_INT)
		dev_dbg(dev, "\tSts Valid Int Support\n");
	if (intfcaps & TPM_INTF_DATA_AVAIL_INT)
		dev_dbg(dev, "\tData Avail Int Support\n");

	/* INTERRUPT Setup */
	init_waitqueue_head(&chip->vendor.read_queue);
	init_waitqueue_head(&chip->vendor.int_queue);

	intmask =
	    ioread32(chip->vendor.iobase +
		     TPM_INT_ENABLE(chip->vendor.locality));

	intmask |= TPM_INTF_CMD_READY_INT
	    | TPM_INTF_LOCALITY_CHANGE_INT | TPM_INTF_DATA_AVAIL_INT
	    | TPM_INTF_STS_VALID_INT;

	iowrite32(intmask,
		  chip->vendor.iobase +
		  TPM_INT_ENABLE(chip->vendor.locality));
	if (interrupts)
		chip->vendor.irq = irq;
	if (interrupts && !chip->vendor.irq) {
		chip->vendor.irq =
		    ioread8(chip->vendor.iobase +
			    TPM_INT_VECTOR(chip->vendor.locality));

		for (i = 3; i < 16 && chip->vendor.irq == 0; i++) {
			iowrite8(i, chip->vendor.iobase +
				    TPM_INT_VECTOR(chip->vendor.locality));
			if (request_irq
			    (i, tis_int_probe, IRQF_SHARED,
			     chip->vendor.miscdev.name, chip) != 0) {
				dev_info(chip->dev,
					 "Unable to request irq: %d for probe\n",
					 i);
				continue;
			}

			/* Clear all existing */
			iowrite32(ioread32
				  (chip->vendor.iobase +
				   TPM_INT_STATUS(chip->vendor.locality)),
				  chip->vendor.iobase +
				  TPM_INT_STATUS(chip->vendor.locality));

			/* Turn on */
			iowrite32(intmask | TPM_GLOBAL_INT_ENABLE,
				  chip->vendor.iobase +
				  TPM_INT_ENABLE(chip->vendor.locality));

			/* Generate Interrupts */
			tpm_gen_interrupt(chip);

			/* Turn off */
			iowrite32(intmask,
				  chip->vendor.iobase +
				  TPM_INT_ENABLE(chip->vendor.locality));
			free_irq(i, chip);
		}
	}
	if (chip->vendor.irq) {
		iowrite8(chip->vendor.irq,
			 chip->vendor.iobase +
			 TPM_INT_VECTOR(chip->vendor.locality));
		if (request_irq
		    (chip->vendor.irq, tis_int_handler, IRQF_SHARED,
		     chip->vendor.miscdev.name, chip) != 0) {
			dev_info(chip->dev,
				 "Unable to request irq: %d for use\n",
				 chip->vendor.irq);
			chip->vendor.irq = 0;
		} else {
			/* Clear all existing */
			iowrite32(ioread32
				  (chip->vendor.iobase +
				   TPM_INT_STATUS(chip->vendor.locality)),
				  chip->vendor.iobase +
				  TPM_INT_STATUS(chip->vendor.locality));

			/* Turn on */
			iowrite32(intmask | TPM_GLOBAL_INT_ENABLE,
				  chip->vendor.iobase +
				  TPM_INT_ENABLE(chip->vendor.locality));
		}
	}

	INIT_LIST_HEAD(&chip->vendor.list);
	spin_lock(&tis_lock);
	list_add(&chip->vendor.list, &tis_chips);
	spin_unlock(&tis_lock);

	tpm_get_timeouts(chip);
	tpm_continue_selftest(chip);

	return 0;
out_err:
	if (chip->vendor.iobase)
		iounmap(chip->vendor.iobase);
	tpm_remove_hardware(chip->dev);
	return rc;
}