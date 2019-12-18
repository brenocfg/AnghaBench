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
struct zd_ioreq32 {int dummy; } ;
struct zd_chip {int /*<<< orphan*/  usb; } ;

/* Variables and functions */
 int _zd_iowrite32v_async_locked (struct zd_chip*,struct zd_ioreq32 const*,unsigned int) ; 
 int zd_usb_iowrite16v_async_end (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zd_usb_iowrite16v_async_start (int /*<<< orphan*/ *) ; 

int _zd_iowrite32v_locked(struct zd_chip *chip, const struct zd_ioreq32 *ioreqs,
			  unsigned int count)
{
	int r;

	zd_usb_iowrite16v_async_start(&chip->usb);
	r = _zd_iowrite32v_async_locked(chip, ioreqs, count);
	if (r) {
		zd_usb_iowrite16v_async_end(&chip->usb, 0);
		return r;
	}
	return zd_usb_iowrite16v_async_end(&chip->usb, 50 /* ms */);
}