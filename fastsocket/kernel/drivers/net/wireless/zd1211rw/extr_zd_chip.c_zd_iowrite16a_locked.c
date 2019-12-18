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
struct zd_ioreq16 {int /*<<< orphan*/  addr; } ;
struct zd_chip {int /*<<< orphan*/  usb; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 unsigned int USB_MAX_IOWRITE16_COUNT ; 
 int /*<<< orphan*/  ZD_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zd_chip_dev (struct zd_chip*) ; 
 int zd_usb_iowrite16v_async (int /*<<< orphan*/ *,struct zd_ioreq16 const*,unsigned int) ; 
 int zd_usb_iowrite16v_async_end (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zd_usb_iowrite16v_async_start (int /*<<< orphan*/ *) ; 

int zd_iowrite16a_locked(struct zd_chip *chip,
                  const struct zd_ioreq16 *ioreqs, unsigned int count)
{
	int r;
	unsigned int i, j, t, max;

	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	zd_usb_iowrite16v_async_start(&chip->usb);

	for (i = 0; i < count; i += j + t) {
		t = 0;
		max = count-i;
		if (max > USB_MAX_IOWRITE16_COUNT)
			max = USB_MAX_IOWRITE16_COUNT;
		for (j = 0; j < max; j++) {
			if (!ioreqs[i+j].addr) {
				t = 1;
				break;
			}
		}

		r = zd_usb_iowrite16v_async(&chip->usb, &ioreqs[i], j);
		if (r) {
			zd_usb_iowrite16v_async_end(&chip->usb, 0);
			dev_dbg_f(zd_chip_dev(chip),
				  "error zd_usb_iowrite16v. Error number %d\n",
				  r);
			return r;
		}
	}

	return zd_usb_iowrite16v_async_end(&chip->usb, 50 /* ms */);
}