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
struct usb_usbvision {scalar_t__ scratch; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_SCRATCH ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,scalar_t__,int) ; 
 int scratch_buf_size ; 

__attribute__((used)) static int scratch_get_extra(struct usb_usbvision *usbvision,
			     unsigned char *data, int *ptr, int len)
{
	int len_part;

	if (*ptr + len < scratch_buf_size) {
		memcpy(data, usbvision->scratch + *ptr, len);
		*ptr += len;
	} else {
		len_part = scratch_buf_size - *ptr;
		memcpy(data, usbvision->scratch + *ptr, len_part);
		if (len == len_part) {
			*ptr = 0;							/* just set the y_ptr to zero */
		} else {
			memcpy(data + len_part, usbvision->scratch, len - len_part);
			*ptr = len - len_part;
		}
	}

	PDEBUG(DBG_SCRATCH, "len=%d, new ptr=%d\n", len, *ptr);

	return len;
}