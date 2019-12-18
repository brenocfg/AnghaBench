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
typedef  int u16 ;
struct nouveau_bios {int dummy; } ;

/* Variables and functions */
 int dcb_gpio_table (struct nouveau_bios*,int*,int*,int*,int*) ; 
 int nv_ro08 (struct nouveau_bios*,int) ; 
 int nv_ro16 (struct nouveau_bios*,int) ; 

__attribute__((used)) static u16
dcb_xpiod_table(struct nouveau_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
{
	u16 data = dcb_gpio_table(bios, ver, hdr, cnt, len);
	if (data && *ver >= 0x40 && *hdr >= 0x06) {
		u16 xpio = nv_ro16(bios, data + 0x04);
		if (xpio) {
			*ver = nv_ro08(bios, data + 0x00);
			*hdr = nv_ro08(bios, data + 0x01);
			*cnt = nv_ro08(bios, data + 0x02);
			*len = nv_ro08(bios, data + 0x03);
			return xpio;
		}
	}
	return 0x0000;
}