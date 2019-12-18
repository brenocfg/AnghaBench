#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  minor; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {scalar_t__ speed; int /*<<< orphan*/  dev; int /*<<< orphan*/  devnum; } ;
struct sisusb_usb_data {int ibufsize; int numobufs; int obufsize; int completein; int present; int ready; struct usb_device* sisusb_dev; int /*<<< orphan*/  wait_q; void* SiS_Pr; scalar_t__* urbstatus; TYPE_1__* urbout_context; void** sisurbout; void* sisurbin; void** obuf; void* ibuf; int /*<<< orphan*/  ioportbase; int /*<<< orphan*/  mmiosize; int /*<<< orphan*/  mmiobase; int /*<<< orphan*/  vrambase; int /*<<< orphan*/  minor; int /*<<< orphan*/  lock; int /*<<< orphan*/  kref; } ;
struct SiS_Private {int dummy; } ;
struct TYPE_2__ {int urbindex; void* sisusb; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MAX_NR_CONSOLES ; 
 int NUMOBUFS ; 
 int SISUSB_IBUF_SIZE ; 
 int SISUSB_OBUF_SIZE ; 
 int /*<<< orphan*/  SISUSB_PCI_IOPORTBASE ; 
 int /*<<< orphan*/  SISUSB_PCI_MEMBASE ; 
 int /*<<< orphan*/  SISUSB_PCI_MMIOBASE ; 
 int /*<<< orphan*/  SISUSB_PCI_MMIOSIZE ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct sisusb_usb_data*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct sisusb_usb_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sisusb_console_init (struct sisusb_usb_data*,scalar_t__,scalar_t__) ; 
 scalar_t__ sisusb_first_vc ; 
 int /*<<< orphan*/  sisusb_free_buffers (struct sisusb_usb_data*) ; 
 int /*<<< orphan*/  sisusb_free_urbs (struct sisusb_usb_data*) ; 
 scalar_t__ sisusb_init_gfxdevice (struct sisusb_usb_data*,int) ; 
 scalar_t__ sisusb_last_vc ; 
 int /*<<< orphan*/  sisusb_testreadwrite (struct sisusb_usb_data*) ; 
 void* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_deregister_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_get_dev (struct usb_device*) ; 
 int usb_register_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct sisusb_usb_data*) ; 
 int /*<<< orphan*/  usb_sisusb_class ; 

__attribute__((used)) static int sisusb_probe(struct usb_interface *intf,
			const struct usb_device_id *id)
{
	struct usb_device *dev = interface_to_usbdev(intf);
	struct sisusb_usb_data *sisusb;
	int retval = 0, i;

	dev_info(&dev->dev, "USB2VGA dongle found at address %d\n",
		dev->devnum);

	/* Allocate memory for our private */
	if (!(sisusb = kzalloc(sizeof(*sisusb), GFP_KERNEL))) {
		dev_err(&sisusb->sisusb_dev->dev, "Failed to allocate memory for private data\n");
		return -ENOMEM;
	}
	kref_init(&sisusb->kref);

	mutex_init(&(sisusb->lock));

	/* Register device */
	if ((retval = usb_register_dev(intf, &usb_sisusb_class))) {
		dev_err(&sisusb->sisusb_dev->dev, "Failed to get a minor for device %d\n",
			dev->devnum);
		retval = -ENODEV;
		goto error_1;
	}

	sisusb->sisusb_dev = dev;
	sisusb->minor      = intf->minor;
	sisusb->vrambase   = SISUSB_PCI_MEMBASE;
	sisusb->mmiobase   = SISUSB_PCI_MMIOBASE;
	sisusb->mmiosize   = SISUSB_PCI_MMIOSIZE;
	sisusb->ioportbase = SISUSB_PCI_IOPORTBASE;
	/* Everything else is zero */

	/* Allocate buffers */
	sisusb->ibufsize = SISUSB_IBUF_SIZE;
	if (!(sisusb->ibuf = kmalloc(SISUSB_IBUF_SIZE, GFP_KERNEL))) {
		dev_err(&sisusb->sisusb_dev->dev, "Failed to allocate memory for input buffer");
		retval = -ENOMEM;
		goto error_2;
	}

	sisusb->numobufs = 0;
	sisusb->obufsize = SISUSB_OBUF_SIZE;
	for (i = 0; i < NUMOBUFS; i++) {
		if (!(sisusb->obuf[i] = kmalloc(SISUSB_OBUF_SIZE, GFP_KERNEL))) {
			if (i == 0) {
				dev_err(&sisusb->sisusb_dev->dev, "Failed to allocate memory for output buffer\n");
				retval = -ENOMEM;
				goto error_3;
			}
			break;
		} else
			sisusb->numobufs++;

	}

	/* Allocate URBs */
	if (!(sisusb->sisurbin = usb_alloc_urb(0, GFP_KERNEL))) {
		dev_err(&sisusb->sisusb_dev->dev, "Failed to allocate URBs\n");
		retval = -ENOMEM;
		goto error_3;
	}
	sisusb->completein = 1;

	for (i = 0; i < sisusb->numobufs; i++) {
		if (!(sisusb->sisurbout[i] = usb_alloc_urb(0, GFP_KERNEL))) {
			dev_err(&sisusb->sisusb_dev->dev, "Failed to allocate URBs\n");
			retval = -ENOMEM;
			goto error_4;
		}
		sisusb->urbout_context[i].sisusb = (void *)sisusb;
		sisusb->urbout_context[i].urbindex = i;
		sisusb->urbstatus[i] = 0;
	}

	dev_info(&sisusb->sisusb_dev->dev, "Allocated %d output buffers\n", sisusb->numobufs);

#ifdef INCL_SISUSB_CON
	/* Allocate our SiS_Pr */
	if (!(sisusb->SiS_Pr = kmalloc(sizeof(struct SiS_Private), GFP_KERNEL))) {
		dev_err(&sisusb->sisusb_dev->dev, "Failed to allocate SiS_Pr\n");
	}
#endif

	/* Do remaining init stuff */

	init_waitqueue_head(&sisusb->wait_q);

	usb_set_intfdata(intf, sisusb);

	usb_get_dev(sisusb->sisusb_dev);

	sisusb->present = 1;

	if (dev->speed == USB_SPEED_HIGH) {
		int initscreen = 1;
#ifdef INCL_SISUSB_CON
		if (sisusb_first_vc > 0 &&
		    sisusb_last_vc > 0 &&
		    sisusb_first_vc <= sisusb_last_vc &&
		    sisusb_last_vc <= MAX_NR_CONSOLES)
			initscreen = 0;
#endif
		if (sisusb_init_gfxdevice(sisusb, initscreen))
			dev_err(&sisusb->sisusb_dev->dev, "Failed to early initialize device\n");

	} else
		dev_info(&sisusb->sisusb_dev->dev, "Not attached to USB 2.0 hub, deferring init\n");

	sisusb->ready = 1;

#ifdef SISUSBENDIANTEST
	dev_dbg(&sisusb->sisusb_dev->dev, "*** RWTEST ***\n");
	sisusb_testreadwrite(sisusb);
	dev_dbg(&sisusb->sisusb_dev->dev, "*** RWTEST END ***\n");
#endif

#ifdef INCL_SISUSB_CON
	sisusb_console_init(sisusb, sisusb_first_vc, sisusb_last_vc);
#endif

	return 0;

error_4:
	sisusb_free_urbs(sisusb);
error_3:
	sisusb_free_buffers(sisusb);
error_2:
	usb_deregister_dev(intf, &usb_sisusb_class);
error_1:
	kfree(sisusb);
	return retval;
}