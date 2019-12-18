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
typedef  int u32 ;
struct lh7a40x_ep {scalar_t__ fifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_OUT_FIFO_WC1 ; 
 int usb_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ int lh7a40x_fifo_read(struct lh7a40x_ep *ep,
					unsigned char *cp, int max)
{
	int bytes;
	int count = usb_read(USB_OUT_FIFO_WC1);
	volatile u32 *fifo = (volatile u32 *)ep->fifo;

	if (count > max)
		count = max;
	bytes = count;
	while (count--)
		*cp++ = *fifo & 0xFF;
	return bytes;
}