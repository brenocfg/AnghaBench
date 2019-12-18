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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct nvbios_dpout {void** script; void* lnkcmp; void* flags; void* mask; void* type; } ;
struct nouveau_bios {int dummy; } ;

/* Variables and functions */
 void* nv_ro08 (struct nouveau_bios*,int) ; 
 void* nv_ro16 (struct nouveau_bios*,int) ; 
 int nvbios_dpout_entry (struct nouveau_bios*,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 

u16
nvbios_dpout_parse(struct nouveau_bios *bios, u8 idx,
		   u8 *ver, u8 *hdr, u8 *cnt, u8 *len,
		   struct nvbios_dpout *info)
{
	u16 data = nvbios_dpout_entry(bios, idx, ver, hdr, cnt, len);
	if (data && *ver) {
		info->type = nv_ro16(bios, data + 0x00);
		info->mask = nv_ro16(bios, data + 0x02);
		switch (*ver) {
		case 0x21:
		case 0x30:
			info->flags     = nv_ro08(bios, data + 0x05);
			info->script[0] = nv_ro16(bios, data + 0x06);
			info->script[1] = nv_ro16(bios, data + 0x08);
			info->lnkcmp    = nv_ro16(bios, data + 0x0a);
			info->script[2] = nv_ro16(bios, data + 0x0c);
			info->script[3] = nv_ro16(bios, data + 0x0e);
			info->script[4] = nv_ro16(bios, data + 0x10);
			break;
		case 0x40:
			info->flags     = nv_ro08(bios, data + 0x04);
			info->script[0] = nv_ro16(bios, data + 0x05);
			info->script[1] = nv_ro16(bios, data + 0x07);
			info->lnkcmp    = nv_ro16(bios, data + 0x09);
			info->script[2] = nv_ro16(bios, data + 0x0b);
			info->script[3] = nv_ro16(bios, data + 0x0d);
			info->script[4] = nv_ro16(bios, data + 0x0f);
			break;
		default:
			data = 0x0000;
			break;
		}
	}
	return data;
}