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
typedef  scalar_t__ u16 ;
struct nvbios_init {struct nouveau_bios* bios; } ;
struct nouveau_bios {int dummy; } ;

/* Variables and functions */
 scalar_t__ init_table (struct nouveau_bios*,scalar_t__*) ; 
 scalar_t__ nv_ro16 (struct nouveau_bios*,scalar_t__) ; 
 int /*<<< orphan*/  warn (char*,...) ; 

__attribute__((used)) static u16
init_table_(struct nvbios_init *init, u16 offset, const char *name)
{
	struct nouveau_bios *bios = init->bios;
	u16 len, data = init_table(bios, &len);
	if (data) {
		if (len >= offset + 2) {
			data = nv_ro16(bios, data + offset);
			if (data)
				return data;

			warn("%s pointer invalid\n", name);
			return 0x0000;
		}

		warn("init data too short for %s pointer", name);
		return 0x0000;
	}

	warn("init data not found\n");
	return 0x0000;
}