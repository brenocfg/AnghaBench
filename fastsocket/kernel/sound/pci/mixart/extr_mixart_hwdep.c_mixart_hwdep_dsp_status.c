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
struct snd_hwdep_dsp_status {int chip_ready; int /*<<< orphan*/  version; int /*<<< orphan*/  num_dsps; int /*<<< orphan*/  id; } ;
struct snd_hwdep {struct mixart_mgr* private_data; } ;
struct mixart_mgr {int dsp_loaded; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIXART_DRIVER_VERSION ; 
 int /*<<< orphan*/  MIXART_HARDW_FILES_MAX_INDEX ; 
 int MIXART_MOTHERBOARD_ELF_INDEX ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mixart_hwdep_dsp_status(struct snd_hwdep *hw,
				   struct snd_hwdep_dsp_status *info)
{
	struct mixart_mgr *mgr = hw->private_data;

	strcpy(info->id, "miXart");
        info->num_dsps = MIXART_HARDW_FILES_MAX_INDEX;

	if (mgr->dsp_loaded & (1 <<  MIXART_MOTHERBOARD_ELF_INDEX))
		info->chip_ready = 1;

	info->version = MIXART_DRIVER_VERSION;
	return 0;
}