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
typedef  int /*<<< orphan*/  u16 ;
struct nvbios_extdev_func {int type; } ;
struct nouveau_bios {int dummy; } ;
typedef  enum nvbios_extdev_type { ____Placeholder_nvbios_extdev_type } nvbios_extdev_type ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  extdev_parse_entry (struct nouveau_bios*,int /*<<< orphan*/ ,struct nvbios_extdev_func*) ; 
 int /*<<< orphan*/  nvbios_extdev_entry (struct nouveau_bios*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 

int
nvbios_extdev_find(struct nouveau_bios *bios, enum nvbios_extdev_type type,
		   struct nvbios_extdev_func *func)
{
	u8 ver, len, i;
	u16 entry;

	i = 0;
	while (!(entry = nvbios_extdev_entry(bios, i++, &ver, &len))) {
		extdev_parse_entry(bios, entry, func);
		if (func->type == type)
			return 0;
	}

	return -EINVAL;
}