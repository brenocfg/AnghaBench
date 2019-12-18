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
typedef  scalar_t__ u16 ;
struct nvbios_dpout {scalar_t__ type; scalar_t__ mask; } ;
struct nouveau_bios {int dummy; } ;

/* Variables and functions */
 scalar_t__ nvbios_dpout_parse (struct nouveau_bios*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,struct nvbios_dpout*) ; 

u16
nvbios_dpout_match(struct nouveau_bios *bios, u16 type, u16 mask,
		   u8 *ver, u8 *hdr, u8 *cnt, u8 *len,
		   struct nvbios_dpout *info)
{
	u16 data, idx = 0;
	while ((data = nvbios_dpout_parse(bios, idx++, ver, hdr, cnt, len, info)) || *ver) {
		if (data && info->type == type) {
			if ((info->mask & mask) == mask)
				break;
		}
	}
	return data;
}