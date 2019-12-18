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
struct usb_usbvision {int /*<<< orphan*/  isocstate; scalar_t__ scratch_headermarker_write_ptr; scalar_t__ scratch_headermarker_read_ptr; scalar_t__ scratch_write_ptr; scalar_t__ scratch_read_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_SCRATCH ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  isoc_state_no_frame ; 

__attribute__((used)) static void scratch_reset(struct usb_usbvision *usbvision)
{
	PDEBUG(DBG_SCRATCH, "\n");

	usbvision->scratch_read_ptr = 0;
	usbvision->scratch_write_ptr = 0;
	usbvision->scratch_headermarker_read_ptr = 0;
	usbvision->scratch_headermarker_write_ptr = 0;
	usbvision->isocstate = isoc_state_no_frame;
}