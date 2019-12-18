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
struct usb_serial {TYPE_2__* dev; } ;
struct TYPE_3__ {int idProduct; } ;
struct TYPE_4__ {TYPE_1__ descriptor; } ;

/* Variables and functions */
#define  QUATECH_DSU2_100 134 
#define  QUATECH_DSU2_400 133 
#define  QUATECH_ESU2_100 132 
#define  QUATECH_ESU2_400 131 
#define  QUATECH_QSU2_100 130 
#define  QUATECH_QSU2_400 129 
#define  QUATECH_SSU2_100 128 

__attribute__((used)) static int qt2_calc_num_ports(struct usb_serial *serial)
{
	int num_ports;
	int flag_as_400;
	switch (serial->dev->descriptor.idProduct) {
	case QUATECH_SSU2_100:
		num_ports = 1;
		break;

	case QUATECH_DSU2_400:
		flag_as_400 = true;
	case QUATECH_DSU2_100:
		num_ports = 2;
	break;

	case QUATECH_QSU2_400:
		flag_as_400 = true;
	case QUATECH_QSU2_100:
		num_ports = 4;
	break;

	case QUATECH_ESU2_400:
		flag_as_400 = true;
	case QUATECH_ESU2_100:
		num_ports = 8;
	break;
	default:
	num_ports = 1;
	break;
	}
	return num_ports;
}