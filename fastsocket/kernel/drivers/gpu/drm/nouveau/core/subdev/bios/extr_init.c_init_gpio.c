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
struct nvbios_init {int offset; int /*<<< orphan*/  bios; } ;
struct nouveau_gpio {int /*<<< orphan*/  (* reset ) (struct nouveau_gpio*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DCB_GPIO_UNUSED ; 
 scalar_t__ init_exec (struct nvbios_init*) ; 
 struct nouveau_gpio* nouveau_gpio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_gpio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void
init_gpio(struct nvbios_init *init)
{
	struct nouveau_gpio *gpio = nouveau_gpio(init->bios);

	trace("GPIO\n");
	init->offset += 1;

	if (init_exec(init) && gpio && gpio->reset)
		gpio->reset(gpio, DCB_GPIO_UNUSED);
}