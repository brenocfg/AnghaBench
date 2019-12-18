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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct nouveau_bios {int dummy; } ;
struct bit_entry {int version; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  bit_entry (struct nouveau_bios*,unsigned char,struct bit_entry*) ; 
 int /*<<< orphan*/  nv_ro08 (struct nouveau_bios*,int) ; 
 int nv_ro16 (struct nouveau_bios*,int /*<<< orphan*/ ) ; 

u16
nvbios_disp_table(struct nouveau_bios *bios,
		  u8 *ver, u8 *hdr, u8 *cnt, u8 *len, u8 *sub)
{
	struct bit_entry U;

	if (!bit_entry(bios, 'U', &U)) {
		if (U.version == 1) {
			u16 data = nv_ro16(bios, U.offset);
			if (data) {
				*ver = nv_ro08(bios, data + 0x00);
				switch (*ver) {
				case 0x20:
				case 0x21:
					*hdr = nv_ro08(bios, data + 0x01);
					*len = nv_ro08(bios, data + 0x02);
					*cnt = nv_ro08(bios, data + 0x03);
					*sub = nv_ro08(bios, data + 0x04);
					return data;
				default:
					break;
				}
			}
		}
	}

	return 0x0000;
}