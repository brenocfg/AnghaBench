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
struct hso_serial {int num_rx_urbs; int /*<<< orphan*/  rx_data_length; int /*<<< orphan*/ * rx_data; int /*<<< orphan*/  ctrl_req_rx; int /*<<< orphan*/ * rx_urb; TYPE_1__* parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int port_spec; TYPE_2__* interface; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_URB_RX_SIZE ; 
 int EINVAL ; 
 int HSO_PORT_MASK ; 
 int /*<<< orphan*/  USB_CDC_GET_ENCAPSULATED_RESPONSE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mux_device_request (struct hso_serial*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hso_mux_serial_read(struct hso_serial *serial)
{
	if (!serial)
		return -EINVAL;

	/* clean data */
	memset(serial->rx_data[0], 0, CTRL_URB_RX_SIZE);
	/* make the request */

	if (serial->num_rx_urbs != 1) {
		dev_err(&serial->parent->interface->dev,
			"ERROR: mux'd reads with multiple buffers "
			"not possible\n");
		return 0;
	}
	return mux_device_request(serial,
				  USB_CDC_GET_ENCAPSULATED_RESPONSE,
				  serial->parent->port_spec & HSO_PORT_MASK,
				  serial->rx_urb[0],
				  &serial->ctrl_req_rx,
				  serial->rx_data[0], serial->rx_data_length);
}