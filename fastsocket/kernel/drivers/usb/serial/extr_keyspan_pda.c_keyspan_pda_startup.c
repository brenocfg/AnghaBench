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
struct usb_serial {TYPE_1__** port; } ;
struct keyspan_pda_private {TYPE_1__* port; struct usb_serial* serial; int /*<<< orphan*/  unthrottle_work; int /*<<< orphan*/  wakeup_work; } ;
struct TYPE_2__ {int /*<<< orphan*/  write_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  keyspan_pda_request_unthrottle ; 
 int /*<<< orphan*/  keyspan_pda_wakeup_write ; 
 struct keyspan_pda_private* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_serial_port_data (TYPE_1__*,struct keyspan_pda_private*) ; 

__attribute__((used)) static int keyspan_pda_startup(struct usb_serial *serial)
{

	struct keyspan_pda_private *priv;

	/* allocate the private data structures for all ports. Well, for all
	   one ports. */

	priv = kmalloc(sizeof(struct keyspan_pda_private), GFP_KERNEL);
	if (!priv)
		return 1; /* error */
	usb_set_serial_port_data(serial->port[0], priv);
	init_waitqueue_head(&serial->port[0]->write_wait);
	INIT_WORK(&priv->wakeup_work, keyspan_pda_wakeup_write);
	INIT_WORK(&priv->unthrottle_work, keyspan_pda_request_unthrottle);
	priv->serial = serial;
	priv->port = serial->port[0];
	return 0;
}