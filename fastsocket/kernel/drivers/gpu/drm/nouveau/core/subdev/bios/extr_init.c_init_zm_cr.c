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
struct nvbios_init {scalar_t__ offset; struct nouveau_bios* bios; } ;
struct nouveau_bios {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_wrvgai (struct nvbios_init*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_ro08 (struct nouveau_bios*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
init_zm_cr(struct nvbios_init *init)
{
	struct nouveau_bios *bios = init->bios;
	u8 addr = nv_ro08(bios, init->offset + 1);
	u8 data = nv_ro08(bios, init->offset + 2);

	trace("ZM_CR\tC[0x%02x] = 0x%02x\n", addr,  data);
	init->offset += 3;

	init_wrvgai(init, 0x03d4, addr, data);
}