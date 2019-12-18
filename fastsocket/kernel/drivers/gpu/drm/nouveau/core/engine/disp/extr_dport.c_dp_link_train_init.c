#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nvbios_init {int execute; int /*<<< orphan*/  offset; int /*<<< orphan*/  crtc; int /*<<< orphan*/  outp; int /*<<< orphan*/  bios; int /*<<< orphan*/  subdev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * script; } ;
struct dp_state {TYPE_1__ info; int /*<<< orphan*/  head; int /*<<< orphan*/  outp; int /*<<< orphan*/  disp; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_bios (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_subdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvbios_exec (struct nvbios_init*) ; 

__attribute__((used)) static void
dp_link_train_init(struct dp_state *dp, bool spread)
{
	struct nvbios_init init = {
		.subdev = nv_subdev(dp->disp),
		.bios = nouveau_bios(dp->disp),
		.outp = dp->outp,
		.crtc = dp->head,
		.execute = 1,
	};

	/* set desired spread */
	if (spread)
		init.offset = dp->info.script[2];
	else
		init.offset = dp->info.script[3];
	nvbios_exec(&init);

	/* pre-train script */
	init.offset = dp->info.script[0];
	nvbios_exec(&init);
}