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
struct TYPE_4__ {int /*<<< orphan*/  version; int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; int /*<<< orphan*/  bustype; } ;
struct rc_dev {char* input_name; void* tx_resolution; void* rx_resolution; void* timeout; void* max_timeout; void* min_timeout; int /*<<< orphan*/  map_name; int /*<<< orphan*/  driver_name; TYPE_2__ input_id; int /*<<< orphan*/  s_tx_carrier; int /*<<< orphan*/  tx_ir; int /*<<< orphan*/  close; int /*<<< orphan*/  open; int /*<<< orphan*/  allowed_protos; int /*<<< orphan*/  driver_type; struct nvt_dev* priv; } ;
struct pnp_device_id {int dummy; } ;
struct pnp_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  queue; int /*<<< orphan*/  lock; } ;
struct nvt_dev {void* cir_wake_addr; scalar_t__ cir_wake_irq; void* cir_addr; scalar_t__ cir_irq; struct rc_dev* rdev; int /*<<< orphan*/  chip_minor; int /*<<< orphan*/  chip_major; TYPE_1__ tx; struct pnp_dev* pdev; int /*<<< orphan*/  rawir; int /*<<< orphan*/  nvt_lock; int /*<<< orphan*/  cr_efdr; int /*<<< orphan*/  cr_efir; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 scalar_t__ CIR_IOREG_LENGTH ; 
 int /*<<< orphan*/  CR_EFDR ; 
 int /*<<< orphan*/  CR_EFIR ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  KERN_NOTICE ; 
 int /*<<< orphan*/  NVT_DRIVER_NAME ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_WINBOND2 ; 
 int /*<<< orphan*/  RC_DRIVER_IR_RAW ; 
 int /*<<< orphan*/  RC_MAP_RC6_MCE ; 
 int /*<<< orphan*/  RC_TYPE_ALL ; 
 void* XYZ ; 
 int /*<<< orphan*/  cir_dump_regs (struct nvt_dev*) ; 
 int /*<<< orphan*/  cir_wake_dump_regs (struct nvt_dev*) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_set_wakeup_enable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct nvt_dev*) ; 
 int /*<<< orphan*/  init_ir_raw_event (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nvt_dev*) ; 
 struct nvt_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvt_cir_isr ; 
 int /*<<< orphan*/  nvt_cir_ldev_init (struct nvt_dev*) ; 
 int /*<<< orphan*/  nvt_cir_regs_init (struct nvt_dev*) ; 
 int /*<<< orphan*/  nvt_cir_wake_isr ; 
 int /*<<< orphan*/  nvt_cir_wake_ldev_init (struct nvt_dev*) ; 
 int /*<<< orphan*/  nvt_cir_wake_regs_init (struct nvt_dev*) ; 
 int /*<<< orphan*/  nvt_close ; 
 int /*<<< orphan*/  nvt_efm_disable (struct nvt_dev*) ; 
 int /*<<< orphan*/  nvt_efm_enable (struct nvt_dev*) ; 
 int nvt_hw_detect (struct nvt_dev*) ; 
 int /*<<< orphan*/  nvt_open ; 
 int /*<<< orphan*/  nvt_pr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nvt_set_tx_carrier ; 
 int /*<<< orphan*/  nvt_tx_ir ; 
 scalar_t__ pnp_irq (struct pnp_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnp_irq_valid (struct pnp_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pnp_port_len (struct pnp_dev*,int) ; 
 void* pnp_port_start (struct pnp_dev*,int) ; 
 int /*<<< orphan*/  pnp_port_valid (struct pnp_dev*,int) ; 
 int /*<<< orphan*/  pnp_set_drvdata (struct pnp_dev*,struct nvt_dev*) ; 
 struct rc_dev* rc_allocate_device () ; 
 int /*<<< orphan*/  rc_free_device (struct rc_dev*) ; 
 int rc_register_device (struct rc_dev*) ; 
 int /*<<< orphan*/  release_region (void*,scalar_t__) ; 
 scalar_t__ request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  request_region (void*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nvt_probe(struct pnp_dev *pdev, const struct pnp_device_id *dev_id)
{
	struct nvt_dev *nvt;
	struct rc_dev *rdev;
	int ret = -ENOMEM;

	nvt = kzalloc(sizeof(struct nvt_dev), GFP_KERNEL);
	if (!nvt)
		return ret;

	/* input device for IR remote (and tx) */
	rdev = rc_allocate_device();
	if (!rdev)
		goto failure;

	ret = -ENODEV;
	/* validate pnp resources */
	if (!pnp_port_valid(pdev, 0) ||
	    pnp_port_len(pdev, 0) < CIR_IOREG_LENGTH) {
		dev_err(&pdev->dev, "IR PNP Port not valid!\n");
		goto failure;
	}

	if (!pnp_irq_valid(pdev, 0)) {
		dev_err(&pdev->dev, "PNP IRQ not valid!\n");
		goto failure;
	}

	if (!pnp_port_valid(pdev, 1) ||
	    pnp_port_len(pdev, 1) < CIR_IOREG_LENGTH) {
		dev_err(&pdev->dev, "Wake PNP Port not valid!\n");
		goto failure;
	}

	nvt->cir_addr = pnp_port_start(pdev, 0);
	nvt->cir_irq  = pnp_irq(pdev, 0);

	nvt->cir_wake_addr = pnp_port_start(pdev, 1);
	/* irq is always shared between cir and cir wake */
	nvt->cir_wake_irq  = nvt->cir_irq;

	nvt->cr_efir = CR_EFIR;
	nvt->cr_efdr = CR_EFDR;

	spin_lock_init(&nvt->nvt_lock);
	spin_lock_init(&nvt->tx.lock);
	init_ir_raw_event(&nvt->rawir);

	ret = -EBUSY;
	/* now claim resources */
	if (!request_region(nvt->cir_addr,
			    CIR_IOREG_LENGTH, NVT_DRIVER_NAME))
		goto failure;

	if (request_irq(nvt->cir_irq, nvt_cir_isr, IRQF_SHARED,
			NVT_DRIVER_NAME, (void *)nvt))
		goto failure;

	if (!request_region(nvt->cir_wake_addr,
			    CIR_IOREG_LENGTH, NVT_DRIVER_NAME))
		goto failure;

	if (request_irq(nvt->cir_wake_irq, nvt_cir_wake_isr, IRQF_SHARED,
			NVT_DRIVER_NAME, (void *)nvt))
		goto failure;

	pnp_set_drvdata(pdev, nvt);
	nvt->pdev = pdev;

	init_waitqueue_head(&nvt->tx.queue);

	ret = nvt_hw_detect(nvt);
	if (ret)
		goto failure;

	/* Initialize CIR & CIR Wake Logical Devices */
	nvt_efm_enable(nvt);
	nvt_cir_ldev_init(nvt);
	nvt_cir_wake_ldev_init(nvt);
	nvt_efm_disable(nvt);

	/* Initialize CIR & CIR Wake Config Registers */
	nvt_cir_regs_init(nvt);
	nvt_cir_wake_regs_init(nvt);

	/* Set up the rc device */
	rdev->priv = nvt;
	rdev->driver_type = RC_DRIVER_IR_RAW;
	rdev->allowed_protos = RC_TYPE_ALL;
	rdev->open = nvt_open;
	rdev->close = nvt_close;
	rdev->tx_ir = nvt_tx_ir;
	rdev->s_tx_carrier = nvt_set_tx_carrier;
	rdev->input_name = "Nuvoton w836x7hg Infrared Remote Transceiver";
	rdev->input_id.bustype = BUS_HOST;
	rdev->input_id.vendor = PCI_VENDOR_ID_WINBOND2;
	rdev->input_id.product = nvt->chip_major;
	rdev->input_id.version = nvt->chip_minor;
	rdev->driver_name = NVT_DRIVER_NAME;
	rdev->map_name = RC_MAP_RC6_MCE;
#if 0
	rdev->min_timeout = XYZ;
	rdev->max_timeout = XYZ;
	rdev->timeout = XYZ;
	/* rx resolution is hardwired to 50us atm, 1, 25, 100 also possible */
	rdev->rx_resolution = XYZ;
	/* tx bits */
	rdev->tx_resolution = XYZ;
#endif

	ret = rc_register_device(rdev);
	if (ret)
		goto failure;

	device_set_wakeup_capable(&pdev->dev, 1);
	device_set_wakeup_enable(&pdev->dev, 1);
	nvt->rdev = rdev;
	nvt_pr(KERN_NOTICE, "driver has been successfully loaded\n");
	if (debug) {
		cir_dump_regs(nvt);
		cir_wake_dump_regs(nvt);
	}

	return 0;

failure:
	if (nvt->cir_irq)
		free_irq(nvt->cir_irq, nvt);
	if (nvt->cir_addr)
		release_region(nvt->cir_addr, CIR_IOREG_LENGTH);

	if (nvt->cir_wake_irq)
		free_irq(nvt->cir_wake_irq, nvt);
	if (nvt->cir_wake_addr)
		release_region(nvt->cir_wake_addr, CIR_IOREG_LENGTH);

	rc_free_device(rdev);
	kfree(nvt);

	return ret;
}