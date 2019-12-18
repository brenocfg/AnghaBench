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
struct snd_soc_codec {int /*<<< orphan*/  ac97; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* warm_reset ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* reset ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ ac97_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 TYPE_1__ soc_ac97_ops ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 scalar_t__* wm9713_reg ; 

int wm9713_reset(struct snd_soc_codec *codec, int try_warm)
{
	if (try_warm && soc_ac97_ops.warm_reset) {
		soc_ac97_ops.warm_reset(codec->ac97);
		if (ac97_read(codec, 0) == wm9713_reg[0])
			return 1;
	}

	soc_ac97_ops.reset(codec->ac97);
	if (soc_ac97_ops.warm_reset)
		soc_ac97_ops.warm_reset(codec->ac97);
	if (ac97_read(codec, 0) != wm9713_reg[0])
		return -EIO;
	return 0;
}