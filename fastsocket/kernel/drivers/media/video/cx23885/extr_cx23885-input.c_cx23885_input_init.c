#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_5__ {int version; int /*<<< orphan*/  product; scalar_t__ vendor; int /*<<< orphan*/  bustype; } ;
struct rc_dev {int driver_type; unsigned long allowed_protos; char* map_name; int /*<<< orphan*/  driver_name; int /*<<< orphan*/  close; int /*<<< orphan*/  open; struct cx23885_kernel_ir* priv; TYPE_2__ dev; TYPE_1__ input_id; struct cx23885_kernel_ir* input_phys; struct cx23885_kernel_ir* input_name; } ;
struct cx23885_kernel_ir {struct cx23885_kernel_ir* name; struct cx23885_kernel_ir* phys; struct rc_dev* rc; struct cx23885_dev* cx; } ;
struct cx23885_dev {int board; struct cx23885_kernel_ir* kernel_ir; TYPE_3__* pci; int /*<<< orphan*/ * sd_ir; } ;
typedef  enum rc_driver_type { ____Placeholder_rc_driver_type } rc_driver_type ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  device; scalar_t__ vendor; int /*<<< orphan*/  subsystem_device; scalar_t__ subsystem_vendor; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_PCI ; 
#define  CX23885_BOARD_HAUPPAUGE_HVR1250 131 
#define  CX23885_BOARD_HAUPPAUGE_HVR1290 130 
#define  CX23885_BOARD_HAUPPAUGE_HVR1850 129 
#define  CX23885_BOARD_TEVII_S470 128 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MODULE_NAME ; 
 int RC_DRIVER_IR_RAW ; 
 char* RC_MAP_RC5_HAUPPAUGE_NEW ; 
 char* RC_MAP_TEVII_NEC ; 
 unsigned long RC_TYPE_ALL ; 
 TYPE_4__* cx23885_boards ; 
 int /*<<< orphan*/  cx23885_input_ir_close ; 
 int /*<<< orphan*/  cx23885_input_ir_open ; 
 int /*<<< orphan*/  cx23885_input_ir_stop (struct cx23885_dev*) ; 
 void* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cx23885_kernel_ir*) ; 
 struct cx23885_kernel_ir* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_name (TYPE_3__*) ; 
 struct rc_dev* rc_allocate_device () ; 
 int /*<<< orphan*/  rc_free_device (struct rc_dev*) ; 
 int rc_register_device (struct rc_dev*) ; 

int cx23885_input_init(struct cx23885_dev *dev)
{
	struct cx23885_kernel_ir *kernel_ir;
	struct rc_dev *rc;
	char *rc_map;
	enum rc_driver_type driver_type;
	unsigned long allowed_protos;

	int ret;

	/*
	 * If the IR device (hardware registers, chip, GPIO lines, etc.) isn't
	 * encapsulated in a v4l2_subdev, then I'm not going to deal with it.
	 */
	if (dev->sd_ir == NULL)
		return -ENODEV;

	switch (dev->board) {
	case CX23885_BOARD_HAUPPAUGE_HVR1850:
	case CX23885_BOARD_HAUPPAUGE_HVR1290:
	case CX23885_BOARD_HAUPPAUGE_HVR1250:
		/* Integrated CX2388[58] IR controller */
		driver_type = RC_DRIVER_IR_RAW;
		allowed_protos = RC_TYPE_ALL;
		/* The grey Hauppauge RC-5 remote */
		rc_map = RC_MAP_RC5_HAUPPAUGE_NEW;
		break;
	case CX23885_BOARD_TEVII_S470:
		/* Integrated CX23885 IR controller */
		driver_type = RC_DRIVER_IR_RAW;
		allowed_protos = RC_TYPE_ALL;
		/* A guess at the remote */
		rc_map = RC_MAP_TEVII_NEC;
		break;
	default:
		return -ENODEV;
	}

	/* cx23885 board instance kernel IR state */
	kernel_ir = kzalloc(sizeof(struct cx23885_kernel_ir), GFP_KERNEL);
	if (kernel_ir == NULL)
		return -ENOMEM;

	kernel_ir->cx = dev;
	kernel_ir->name = kasprintf(GFP_KERNEL, "cx23885 IR (%s)",
				    cx23885_boards[dev->board].name);
	kernel_ir->phys = kasprintf(GFP_KERNEL, "pci-%s/ir0",
				    pci_name(dev->pci));

	/* input device */
	rc = rc_allocate_device();
	if (!rc) {
		ret = -ENOMEM;
		goto err_out_free;
	}

	kernel_ir->rc = rc;
	rc->input_name = kernel_ir->name;
	rc->input_phys = kernel_ir->phys;
	rc->input_id.bustype = BUS_PCI;
	rc->input_id.version = 1;
	if (dev->pci->subsystem_vendor) {
		rc->input_id.vendor  = dev->pci->subsystem_vendor;
		rc->input_id.product = dev->pci->subsystem_device;
	} else {
		rc->input_id.vendor  = dev->pci->vendor;
		rc->input_id.product = dev->pci->device;
	}
	rc->dev.parent = &dev->pci->dev;
	rc->driver_type = driver_type;
	rc->allowed_protos = allowed_protos;
	rc->priv = kernel_ir;
	rc->open = cx23885_input_ir_open;
	rc->close = cx23885_input_ir_close;
	rc->map_name = rc_map;
	rc->driver_name = MODULE_NAME;

	/* Go */
	dev->kernel_ir = kernel_ir;
	ret = rc_register_device(rc);
	if (ret)
		goto err_out_stop;

	return 0;

err_out_stop:
	cx23885_input_ir_stop(dev);
	dev->kernel_ir = NULL;
	rc_free_device(rc);
err_out_free:
	kfree(kernel_ir->phys);
	kfree(kernel_ir->name);
	kfree(kernel_ir);
	return ret;
}