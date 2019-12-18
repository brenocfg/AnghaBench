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
struct usb_usbvision {int scratch_read_ptr; int scratch_write_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_SCRATCH ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ scratch_buf_size ; 

__attribute__((used)) static int scratch_free(struct usb_usbvision *usbvision)
{
	int free = usbvision->scratch_read_ptr - usbvision->scratch_write_ptr;
	if (free <= 0)
		free += scratch_buf_size;
	if (free) {
		free -= 1;							/* at least one byte in the buffer must */
										/* left blank, otherwise there is no chance to differ between full and empty */
	}
	PDEBUG(DBG_SCRATCH, "return %d\n", free);

	return free;
}