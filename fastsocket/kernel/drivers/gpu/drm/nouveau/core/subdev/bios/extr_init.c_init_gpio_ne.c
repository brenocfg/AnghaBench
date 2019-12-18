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
struct nvbios_init {scalar_t__ offset; struct nouveau_bios* bios; } ;
struct nouveau_gpio {int /*<<< orphan*/  (* reset ) (struct nouveau_gpio*,scalar_t__) ;} ;
struct nouveau_bios {int dummy; } ;
struct dcb_gpio_func {scalar_t__ func; } ;

/* Variables and functions */
 scalar_t__ DCB_GPIO_UNUSED ; 
 int /*<<< orphan*/  cont (char*,...) ; 
 scalar_t__ dcb_gpio_parse (struct nouveau_bios*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,struct dcb_gpio_func*) ; 
 scalar_t__ init_exec (struct nvbios_init*) ; 
 struct nouveau_gpio* nouveau_gpio (struct nouveau_bios*) ; 
 scalar_t__ nv_ro08 (struct nouveau_bios*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_gpio*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,...) ; 

__attribute__((used)) static void
init_gpio_ne(struct nvbios_init *init)
{
	struct nouveau_bios *bios = init->bios;
	struct nouveau_gpio *gpio = nouveau_gpio(bios);
	struct dcb_gpio_func func;
	u8 count = nv_ro08(bios, init->offset + 1);
	u8 idx = 0, ver, len;
	u16 data, i;

	trace("GPIO_NE\t");
	init->offset += 2;

	for (i = init->offset; i < init->offset + count; i++)
		cont("0x%02x ", nv_ro08(bios, i));
	cont("\n");

	while ((data = dcb_gpio_parse(bios, 0, idx++, &ver, &len, &func))) {
		if (func.func != DCB_GPIO_UNUSED) {
			for (i = init->offset; i < init->offset + count; i++) {
				if (func.func == nv_ro08(bios, i))
					break;
			}

			trace("\tFUNC[0x%02x]", func.func);
			if (i == (init->offset + count)) {
				cont(" *");
				if (init_exec(init) && gpio && gpio->reset)
					gpio->reset(gpio, func.func);
			}
			cont("\n");
		}
	}

	init->offset += count;
}