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
struct nouveau_bios {int bmp_offset; } ;
struct bit_entry {int version; int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  bit_entry (struct nouveau_bios*,char,struct bit_entry*) ; 
 int /*<<< orphan*/  nv_error (struct nouveau_bios*,char*,int) ; 
 int nv_ro08 (struct nouveau_bios*,int) ; 
 int nv_ro16 (struct nouveau_bios*,int) ; 

__attribute__((used)) static u16
perf_table(struct nouveau_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
{
	struct bit_entry bit_P;
	u16 perf = 0x0000;

	if (!bit_entry(bios, 'P', &bit_P)) {
		if (bit_P.version <= 2) {
			perf = nv_ro16(bios, bit_P.offset + 0);
			if (perf) {
				*ver = nv_ro08(bios, perf + 0);
				*hdr = nv_ro08(bios, perf + 1);
			}
		} else
			nv_error(bios, "unknown offset for perf in BIT P %d\n",
				bit_P.version);
	}

	if (bios->bmp_offset) {
		if (nv_ro08(bios, bios->bmp_offset + 6) >= 0x25) {
			perf = nv_ro16(bios, bios->bmp_offset + 0x94);
			if (perf) {
				*hdr = nv_ro08(bios, perf + 0);
				*ver = nv_ro08(bios, perf + 1);
			}
		}
	}

	return perf;
}