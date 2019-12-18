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
struct nouveau_devinit {int /*<<< orphan*/  (* meminit ) (struct nouveau_devinit*) ;} ;

/* Variables and functions */
 scalar_t__ init_exec (struct nvbios_init*) ; 
 int /*<<< orphan*/  init_exec_force (struct nvbios_init*,int) ; 
 struct nouveau_devinit* nouveau_devinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_devinit*) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void
init_compute_mem(struct nvbios_init *init)
{
	struct nouveau_devinit *devinit = nouveau_devinit(init->bios);

	trace("COMPUTE_MEM\n");
	init->offset += 1;

	init_exec_force(init, true);
	if (init_exec(init) && devinit->meminit)
		devinit->meminit(devinit);
	init_exec_force(init, false);
}