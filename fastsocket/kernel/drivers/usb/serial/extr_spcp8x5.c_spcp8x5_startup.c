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
typedef  int u16 ;
struct usb_serial {int num_ports; int /*<<< orphan*/ * port; TYPE_2__* dev; } ;
struct spcp8x5_private {int type; int /*<<< orphan*/ * buf; int /*<<< orphan*/  delta_msr_wait; int /*<<< orphan*/  lock; } ;
typedef  enum spcp8x5_type { ____Placeholder_spcp8x5_type } spcp8x5_type ;
struct TYPE_3__ {scalar_t__ idVendor; int /*<<< orphan*/  idProduct; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; TYPE_1__ descriptor; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SPCP825_007_TYPE ; 
 int SPCP825_008_TYPE ; 
 int SPCP825_INTERMATIC_TYPE ; 
 int SPCP825_PHILIP_TYPE ; 
 int SPCP835_TYPE ; 
 int /*<<< orphan*/  SPCP8x5_BUF_SIZE ; 
 int /*<<< orphan*/ * alloc_ringbuf (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  free_ringbuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct spcp8x5_private*) ; 
 struct spcp8x5_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct spcp8x5_private* usb_get_serial_port_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_serial_port_data (int /*<<< orphan*/ ,struct spcp8x5_private*) ; 

__attribute__((used)) static int spcp8x5_startup(struct usb_serial *serial)
{
	struct spcp8x5_private *priv;
	int i;
	enum spcp8x5_type type = SPCP825_007_TYPE;
	u16 product = le16_to_cpu(serial->dev->descriptor.idProduct);

	if (product == 0x0201)
		type = SPCP825_007_TYPE;
	else if (product == 0x0231)
		type = SPCP835_TYPE;
	else if (product == 0x0235)
		type = SPCP825_008_TYPE;
	else if (product == 0x0204)
		type = SPCP825_INTERMATIC_TYPE;
	else if (product == 0x0471 &&
		 serial->dev->descriptor.idVendor == cpu_to_le16(0x081e))
		type = SPCP825_PHILIP_TYPE;
	dev_dbg(&serial->dev->dev, "device type = %d\n", (int)type);

	for (i = 0; i < serial->num_ports; ++i) {
		priv = kzalloc(sizeof(struct spcp8x5_private), GFP_KERNEL);
		if (!priv)
			goto cleanup;

		spin_lock_init(&priv->lock);
		priv->buf = alloc_ringbuf(SPCP8x5_BUF_SIZE);
		if (priv->buf == NULL)
			goto cleanup2;

		init_waitqueue_head(&priv->delta_msr_wait);
		priv->type = type;
		usb_set_serial_port_data(serial->port[i] , priv);

	}

	return 0;

cleanup2:
	kfree(priv);
cleanup:
	for (--i; i >= 0; --i) {
		priv = usb_get_serial_port_data(serial->port[i]);
		free_ringbuf(priv->buf);
		kfree(priv);
		usb_set_serial_port_data(serial->port[i] , NULL);
	}
	return -ENOMEM;
}