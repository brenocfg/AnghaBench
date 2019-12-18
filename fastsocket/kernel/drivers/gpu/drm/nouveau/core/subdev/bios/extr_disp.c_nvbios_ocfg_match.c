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
typedef  scalar_t__ u16 ;
struct nvbios_ocfg {scalar_t__ match; } ;
struct nouveau_bios {int dummy; } ;

/* Variables and functions */
 scalar_t__ nvbios_ocfg_parse (struct nouveau_bios*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nvbios_ocfg*) ; 

u16
nvbios_ocfg_match(struct nouveau_bios *bios, u16 outp, u16 type,
		  u8 *ver, u8 *hdr, u8 *cnt, u8 *len,
		  struct nvbios_ocfg *info)
{
	u16 data, idx = 0;
	while ((data = nvbios_ocfg_parse(bios, outp, idx++, ver, hdr, cnt, len, info))) {
		if (info->match == type)
			break;
	}
	return data;
}