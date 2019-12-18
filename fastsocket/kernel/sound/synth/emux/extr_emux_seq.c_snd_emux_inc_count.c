#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  owner; } ;
struct snd_emux {int /*<<< orphan*/  used; TYPE_2__ ops; TYPE_1__* card; } ;
struct TYPE_3__ {int /*<<< orphan*/  module; } ;

/* Variables and functions */
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

int
snd_emux_inc_count(struct snd_emux *emu)
{
	emu->used++;
	if (!try_module_get(emu->ops.owner))
		goto __error;
	if (!try_module_get(emu->card->module)) {
		module_put(emu->ops.owner);
	      __error:
		emu->used--;
		return 0;
	}
	return 1;
}