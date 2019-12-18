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
struct zd_usb {scalar_t__ initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zd_op_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zd_usb_dev (struct zd_usb*) ; 
 int /*<<< orphan*/  zd_usb_disable_int (struct zd_usb*) ; 
 int /*<<< orphan*/  zd_usb_disable_rx (struct zd_usb*) ; 
 int /*<<< orphan*/  zd_usb_disable_tx (struct zd_usb*) ; 
 int /*<<< orphan*/  zd_usb_to_hw (struct zd_usb*) ; 

__attribute__((used)) static void zd_usb_stop(struct zd_usb *usb)
{
	dev_dbg_f(zd_usb_dev(usb), "\n");

	zd_op_stop(zd_usb_to_hw(usb));

	zd_usb_disable_tx(usb);
	zd_usb_disable_rx(usb);
	zd_usb_disable_int(usb);

	usb->initialized = 0;
}