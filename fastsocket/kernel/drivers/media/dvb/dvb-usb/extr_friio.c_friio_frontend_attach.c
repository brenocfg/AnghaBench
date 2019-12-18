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
struct dvb_usb_adapter {int /*<<< orphan*/ * fe; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ friio_initialize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * jdvbt90502_attach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int friio_frontend_attach(struct dvb_usb_adapter *adap)
{
	if (friio_initialize(adap->dev) < 0)
		return -EIO;

	adap->fe = jdvbt90502_attach(adap->dev);
	if (adap->fe == NULL)
		return -EIO;

	return 0;
}