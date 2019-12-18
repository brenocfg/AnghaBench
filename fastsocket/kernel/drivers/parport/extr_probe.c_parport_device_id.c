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
struct pardevice {int /*<<< orphan*/  daisy; int /*<<< orphan*/  port; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENXIO ; 
 int IEEE1284_DEVICEID ; 
 int IEEE1284_MODE_COMPAT ; 
 int IEEE1284_MODE_NIBBLE ; 
 int /*<<< orphan*/  parport_claim_or_block (struct pardevice*) ; 
 int /*<<< orphan*/  parport_close (struct pardevice*) ; 
 int parport_negotiate (int /*<<< orphan*/ ,int) ; 
 struct pardevice* parport_open (int,char*) ; 
 int parport_read_device_id (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  parport_release (struct pardevice*) ; 
 int /*<<< orphan*/  parse_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

ssize_t parport_device_id (int devnum, char *buffer, size_t count)
{
	ssize_t retval = -ENXIO;
	struct pardevice *dev = parport_open (devnum, "Device ID probe");
	if (!dev)
		return -ENXIO;

	parport_claim_or_block (dev);

	/* Negotiate to compatibility mode, and then to device ID
	 * mode. (This so that we start form beginning of device ID if
	 * already in device ID mode.) */
	parport_negotiate (dev->port, IEEE1284_MODE_COMPAT);
	retval = parport_negotiate (dev->port,
				    IEEE1284_MODE_NIBBLE | IEEE1284_DEVICEID);

	if (!retval) {
		retval = parport_read_device_id (dev->port, buffer, count);
		parport_negotiate (dev->port, IEEE1284_MODE_COMPAT);
		if (retval > 2)
			parse_data (dev->port, dev->daisy, buffer+2);
	}

	parport_release (dev);
	parport_close (dev);
	return retval;
}