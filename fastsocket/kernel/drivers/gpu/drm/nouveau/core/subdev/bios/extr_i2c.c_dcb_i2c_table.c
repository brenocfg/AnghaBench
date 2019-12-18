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
dcb_i2c_table(struct nouveau_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
{
	u16 i2c = 0x0000;
	u16 dcb = dcb_table(bios, ver, hdr, cnt, len);
	if (dcb) {
		if (*ver >= 0x15)
			i2c = nv_ro16(bios, dcb + 2);
		if (*ver >= 0x30)
			i2c = nv_ro16(bios, dcb + 4);
	}

	if (i2c && *ver >= 0x30) {
		*ver = nv_ro08(bios, i2c + 0);
		*hdr = nv_ro08(bios, i2c + 1);
		*cnt = nv_ro08(bios, i2c + 2);
		*len = nv_ro08(bios, i2c + 3);
	} else {
		*ver = *ver; /* use DCB version */
		*hdr = 0;
		*cnt = 16;
		*len = 4;
	}

	return i2c;
}