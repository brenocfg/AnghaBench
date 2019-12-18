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
typedef  int u8 ;
struct sisusb_usb_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SISUSB_TYPE_IO ; 
 int sisusb_read_memio_byte (struct sisusb_usb_data*,int /*<<< orphan*/ ,int,int*) ; 
 int sisusb_write_memio_byte (struct sisusb_usb_data*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
sisusb_setidxregmask(struct sisusb_usb_data *sisusb, int port, u8 idx,
							u8 data, u8 mask)
{
	int ret;
	u8 tmp;
	ret = sisusb_write_memio_byte(sisusb, SISUSB_TYPE_IO, port, idx);
	ret |= sisusb_read_memio_byte(sisusb, SISUSB_TYPE_IO, port + 1, &tmp);
	tmp &= ~(mask);
	tmp |= (data & mask);
	ret |= sisusb_write_memio_byte(sisusb, SISUSB_TYPE_IO, port + 1, tmp);
	return ret;
}