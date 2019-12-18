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
struct TYPE_3__ {int /*<<< orphan*/  dsp_load; int /*<<< orphan*/  dsp_status; } ;
struct snd_hwdep {int exclusive; int /*<<< orphan*/  name; TYPE_1__ ops; struct mixart_mgr* private_data; int /*<<< orphan*/  iface; } ;
struct mixart_mgr {TYPE_2__** chip; scalar_t__ dsp_loaded; } ;
struct TYPE_4__ {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_HWDEP_IFACE_MIXART ; 
 char* SND_MIXART_HWDEP_ID ; 
 int /*<<< orphan*/  mixart_hwdep_dsp_load ; 
 int /*<<< orphan*/  mixart_hwdep_dsp_status ; 
 int snd_card_register (int /*<<< orphan*/ ) ; 
 int snd_hwdep_new (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct snd_hwdep**) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 

int snd_mixart_setup_firmware(struct mixart_mgr *mgr)
{
	int err;
	struct snd_hwdep *hw;

	/* only create hwdep interface for first cardX (see "index" module parameter)*/
	if ((err = snd_hwdep_new(mgr->chip[0]->card, SND_MIXART_HWDEP_ID, 0, &hw)) < 0)
		return err;

	hw->iface = SNDRV_HWDEP_IFACE_MIXART;
	hw->private_data = mgr;
	hw->ops.dsp_status = mixart_hwdep_dsp_status;
	hw->ops.dsp_load = mixart_hwdep_dsp_load;
	hw->exclusive = 1;
	sprintf(hw->name,  SND_MIXART_HWDEP_ID);
	mgr->dsp_loaded = 0;

	return snd_card_register(mgr->chip[0]->card);
}