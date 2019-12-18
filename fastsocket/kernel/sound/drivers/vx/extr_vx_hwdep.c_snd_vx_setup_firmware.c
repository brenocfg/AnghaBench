#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vx_core {TYPE_2__* card; struct snd_hwdep* hwdep; } ;
struct TYPE_4__ {int /*<<< orphan*/  dsp_load; int /*<<< orphan*/  dsp_status; } ;
struct snd_hwdep {int exclusive; int /*<<< orphan*/  name; TYPE_1__ ops; struct vx_core* private_data; int /*<<< orphan*/  iface; } ;
struct TYPE_5__ {char* driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_HWDEP_IFACE_VX ; 
 int /*<<< orphan*/  SND_VX_HWDEP_ID ; 
 int snd_card_register (TYPE_2__*) ; 
 int snd_hwdep_new (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_hwdep**) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  vx_hwdep_dsp_load ; 
 int /*<<< orphan*/  vx_hwdep_dsp_status ; 

int snd_vx_setup_firmware(struct vx_core *chip)
{
	int err;
	struct snd_hwdep *hw;

	if ((err = snd_hwdep_new(chip->card, SND_VX_HWDEP_ID, 0, &hw)) < 0)
		return err;

	hw->iface = SNDRV_HWDEP_IFACE_VX;
	hw->private_data = chip;
	hw->ops.dsp_status = vx_hwdep_dsp_status;
	hw->ops.dsp_load = vx_hwdep_dsp_load;
	hw->exclusive = 1;
	sprintf(hw->name, "VX Loader (%s)", chip->card->driver);
	chip->hwdep = hw;

	return snd_card_register(chip->card);
}