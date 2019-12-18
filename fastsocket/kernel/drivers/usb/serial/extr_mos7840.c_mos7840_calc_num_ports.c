#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct usb_serial {int num_ports; int num_bulk_in; int num_bulk_out; TYPE_5__* interface; } ;
struct TYPE_10__ {TYPE_4__* cur_altsetting; TYPE_2__* altsetting; } ;
struct TYPE_8__ {int bNumEndpoints; } ;
struct TYPE_9__ {TYPE_3__ desc; } ;
struct TYPE_6__ {scalar_t__ bNumEndpoints; } ;
struct TYPE_7__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*,int,...) ; 

__attribute__((used)) static int mos7840_calc_num_ports(struct usb_serial *serial)
{
	int mos7840_num_ports = 0;

	dbg("numberofendpoints: cur %d, alt %d",
	    (int)serial->interface->cur_altsetting->desc.bNumEndpoints,
	    (int)serial->interface->altsetting->desc.bNumEndpoints);
	if (serial->interface->cur_altsetting->desc.bNumEndpoints == 5) {
		mos7840_num_ports = serial->num_ports = 2;
	} else if (serial->interface->cur_altsetting->desc.bNumEndpoints == 9) {
		serial->num_bulk_in = 4;
		serial->num_bulk_out = 4;
		mos7840_num_ports = serial->num_ports = 4;
	}
	dbg ("mos7840_num_ports = %d", mos7840_num_ports);
	return mos7840_num_ports;
}