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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct pll_mapping {scalar_t__ reg; int type; } ;
struct nouveau_bios {int dummy; } ;

/* Variables and functions */
 int nv_ro08 (struct nouveau_bios*,int) ; 
 scalar_t__ nv_ro32 (struct nouveau_bios*,int) ; 
 int pll_limits_table (struct nouveau_bios*,int*,int*,int*,int*) ; 
 struct pll_mapping* pll_map (struct nouveau_bios*) ; 

__attribute__((used)) static u16
pll_map_type(struct nouveau_bios *bios, u8 type, u32 *reg, u8 *ver, u8 *len)
{
	struct pll_mapping *map;
	u8  hdr, cnt;
	u16 data;

	data = pll_limits_table(bios, ver, &hdr, &cnt, len);
	if (data && *ver >= 0x30) {
		data += hdr;
		while (cnt--) {
			if (nv_ro08(bios, data + 0) == type) {
				*reg = nv_ro32(bios, data + 3);
				return data;
			}
			data += *len;
		}
		return 0x0000;
	}

	map = pll_map(bios);
	while (map->reg) {
		if (map->type == type && *ver >= 0x20) {
			u16 addr = (data += hdr);
			*reg = map->reg;
			while (cnt--) {
				if (nv_ro32(bios, data) == map->reg)
					return data;
				data += *len;
			}
			return addr;
		} else
		if (map->type == type) {
			*reg = map->reg;
			return data + 1;
		}
		map++;
	}

	return 0x0000;
}