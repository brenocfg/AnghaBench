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
struct dvb_device {int dummy; } ;
struct dvb_adapter {int dummy; } ;
struct dst_state {struct dvb_device* dst_ca; } ;

/* Variables and functions */
 int /*<<< orphan*/  DST_CA_ERROR ; 
 int /*<<< orphan*/  DVB_DEVICE_CA ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ dvb_register_device (struct dvb_adapter*,struct dvb_device**,int /*<<< orphan*/ *,struct dst_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvbdev_ca ; 
 int /*<<< orphan*/  verbose ; 

struct dvb_device *dst_ca_attach(struct dst_state *dst, struct dvb_adapter *dvb_adapter)
{
	struct dvb_device *dvbdev;

	dprintk(verbose, DST_CA_ERROR, 1, "registering DST-CA device");
	if (dvb_register_device(dvb_adapter, &dvbdev, &dvbdev_ca, dst, DVB_DEVICE_CA) == 0) {
		dst->dst_ca = dvbdev;
		return dst->dst_ca;
	}

	return NULL;
}