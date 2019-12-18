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
typedef  scalar_t__ u32 ;
struct sisusb_usb_data {int vramsize; scalar_t__ vrambase; } ;

/* Variables and functions */
 int /*<<< orphan*/  SISUSB_TYPE_MEM ; 
 int sisusb_clear_vram (struct sisusb_usb_data*,scalar_t__,int) ; 
 int sisusb_write_memio_word (struct sisusb_usb_data*,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int
sisusb_setup_screen(struct sisusb_usb_data *sisusb, int clrall, int drwfr)
{
	int ret = 0;
	u32 address;
	int i, length, modex, modey, bpp;

	modex = 640; modey = 480; bpp = 2;

	address = sisusb->vrambase;	/* Clear video ram */

	if (clrall)
		length = sisusb->vramsize;
	else
		length = modex * bpp * modey;

	ret = sisusb_clear_vram(sisusb, address, length);

	if (!ret && drwfr) {
		for (i = 0; i < modex; i++) {
			address = sisusb->vrambase + (i * bpp);
			ret |= sisusb_write_memio_word(sisusb, SISUSB_TYPE_MEM,
							address, 0xf100);
			address += (modex * (modey-1) * bpp);
			ret |= sisusb_write_memio_word(sisusb, SISUSB_TYPE_MEM,
							address, 0xf100);
		}
		for (i = 0; i < modey; i++) {
			address = sisusb->vrambase + ((i * modex) * bpp);
			ret |= sisusb_write_memio_word(sisusb, SISUSB_TYPE_MEM,
							address, 0xf100);
			address += ((modex - 1) * bpp);
			ret |= sisusb_write_memio_word(sisusb, SISUSB_TYPE_MEM,
							address, 0xf100);
		}
	}

	return ret;
}