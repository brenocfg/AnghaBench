#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dvb_usb_adapter {int /*<<< orphan*/ * fe; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_frontend_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_frontend (int /*<<< orphan*/ *) ; 

int dvb_usb_adapter_frontend_exit(struct dvb_usb_adapter *adap)
{
	if (adap->fe != NULL) {
		dvb_unregister_frontend(adap->fe);
		dvb_frontend_detach(adap->fe);
	}
	return 0;
}