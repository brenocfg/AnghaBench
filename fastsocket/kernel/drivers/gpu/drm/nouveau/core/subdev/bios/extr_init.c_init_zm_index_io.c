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
typedef  int /*<<< orphan*/  u16 ;
struct nvbios_init {scalar_t__ offset; struct nouveau_bios* bios; } ;
struct nouveau_bios {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_wrvgai (struct nvbios_init*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_ro08 (struct nouveau_bios*,scalar_t__) ; 
 int /*<<< orphan*/  nv_ro16 (struct nouveau_bios*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
init_zm_index_io(struct nvbios_init *init)
{
	struct nouveau_bios *bios = init->bios;
	u16 port = nv_ro16(bios, init->offset + 1);
	u8 index = nv_ro08(bios, init->offset + 3);
	u8  data = nv_ro08(bios, init->offset + 4);

	trace("ZM_INDEX_IO\tI[0x%04x][0x%02x] = 0x%02x\n", port, index, data);
	init->offset += 5;

	init_wrvgai(init, port, index, data);
}