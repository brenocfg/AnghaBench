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
 int dcb_table (struct nouveau_bios*,int*,int*,int*,int*) ; 
 int nv_ro08 (struct nouveau_bios*,int) ; 
 int nv_ro16 (struct nouveau_bios*,int) ; 

u16
dcb_gpio_table(struct nouveau_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
{
	u16 data = 0x0000;
	u16 dcb = dcb_table(bios, ver, hdr, cnt, len);
	if (dcb) {
		if (*ver >= 0x30 && *hdr >= 0x0c)
			data = nv_ro16(bios, dcb + 0x0a);
		else
		if (*ver >= 0x22 && nv_ro08(bios, dcb - 1) >= 0x13)
			data = nv_ro16(bios, dcb - 0x0f);

		if (data) {
			*ver = nv_ro08(bios, data + 0x00);
			if (*ver < 0x30) {
				*hdr = 3;
				*cnt = nv_ro08(bios, data + 0x02);
				*len = nv_ro08(bios, data + 0x01);
			} else
			if (*ver <= 0x41) {
				*hdr = nv_ro08(bios, data + 0x01);
				*cnt = nv_ro08(bios, data + 0x02);
				*len = nv_ro08(bios, data + 0x03);
			} else {
				data = 0x0000;
			}
		}
	}
	return data;
}