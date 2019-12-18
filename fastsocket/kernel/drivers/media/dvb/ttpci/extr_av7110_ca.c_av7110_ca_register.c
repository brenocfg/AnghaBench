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
struct av7110 {int /*<<< orphan*/  ca_dev; int /*<<< orphan*/  dvb_adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVB_DEVICE_CA ; 
 int dvb_register_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct av7110*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvbdev_ca ; 

int av7110_ca_register(struct av7110 *av7110)
{
	return dvb_register_device(&av7110->dvb_adapter, &av7110->ca_dev,
				   &dvbdev_ca, av7110, DVB_DEVICE_CA);
}