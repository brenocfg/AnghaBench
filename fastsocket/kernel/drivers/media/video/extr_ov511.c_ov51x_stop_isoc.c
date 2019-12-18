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
struct usb_ov511 {scalar_t__ bclass; scalar_t__ streaming; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BCL_OV518 ; 
 int /*<<< orphan*/  PDEBUG (int,char*) ; 
 int /*<<< orphan*/  ov511_set_packet_size (struct usb_ov511*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ov518_set_packet_size (struct usb_ov511*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ov51x_unlink_isoc (struct usb_ov511*) ; 

__attribute__((used)) static void
ov51x_stop_isoc(struct usb_ov511 *ov)
{
	if (!ov->streaming || !ov->dev)
		return;

	PDEBUG(3, "*** Stopping capture ***");

	if (ov->bclass == BCL_OV518)
		ov518_set_packet_size(ov, 0);
	else
		ov511_set_packet_size(ov, 0);

	ov->streaming = 0;

	ov51x_unlink_isoc(ov);
}