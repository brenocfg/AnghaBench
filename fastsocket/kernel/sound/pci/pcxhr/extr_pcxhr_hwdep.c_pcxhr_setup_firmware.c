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
struct snd_hwdep {int exclusive; int dsp_loaded; int /*<<< orphan*/  name; TYPE_1__ ops; struct pcxhr_mgr* private_data; int /*<<< orphan*/  iface; } ;
struct pcxhr_mgr {TYPE_2__** chip; scalar_t__ dsp_loaded; scalar_t__ is_hr_stereo; } ;
struct TYPE_4__ {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 char* PCXHR_HWDEP_ID ; 
 int /*<<< orphan*/  SNDRV_HWDEP_IFACE_PCXHR ; 
 int /*<<< orphan*/  pcxhr_hwdep_dsp_load ; 
 int /*<<< orphan*/  pcxhr_hwdep_dsp_status ; 
 int snd_card_register (int /*<<< orphan*/ ) ; 
 int snd_hwdep_new (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct snd_hwdep**) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 

int pcxhr_setup_firmware(struct pcxhr_mgr *mgr)
{
	int err;
	struct snd_hwdep *hw;

	/* only create hwdep interface for first cardX
	 * (see "index" module parameter)
	 */
	err = snd_hwdep_new(mgr->chip[0]->card, PCXHR_HWDEP_ID, 0, &hw);
	if (err < 0)
		return err;

	hw->iface = SNDRV_HWDEP_IFACE_PCXHR;
	hw->private_data = mgr;
	hw->ops.dsp_status = pcxhr_hwdep_dsp_status;
	hw->ops.dsp_load = pcxhr_hwdep_dsp_load;
	hw->exclusive = 1;
	/* stereo cards don't need fw_file_0 -> dsp_loaded = 1 */
	hw->dsp_loaded = mgr->is_hr_stereo ? 1 : 0;
	mgr->dsp_loaded = 0;
	sprintf(hw->name, PCXHR_HWDEP_ID);

	err = snd_card_register(mgr->chip[0]->card);
	if (err < 0)
		return err;
	return 0;
}