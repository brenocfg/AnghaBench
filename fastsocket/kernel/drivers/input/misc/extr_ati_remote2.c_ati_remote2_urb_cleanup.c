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
struct ati_remote2 {int /*<<< orphan*/ * buf_dma; int /*<<< orphan*/ * buf; int /*<<< orphan*/  udev; int /*<<< orphan*/ * urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_buffer_free (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ati_remote2_urb_cleanup(struct ati_remote2 *ar2)
{
	int i;

	for (i = 0; i < 2; i++) {
		usb_free_urb(ar2->urb[i]);
		usb_buffer_free(ar2->udev, 4, ar2->buf[i], ar2->buf_dma[i]);
	}
}