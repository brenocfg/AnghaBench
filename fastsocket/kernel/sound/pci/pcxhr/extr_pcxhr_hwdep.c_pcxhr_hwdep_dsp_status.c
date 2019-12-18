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
struct snd_hwdep {int dsp_loaded; struct pcxhr_mgr* private_data; } ;
struct pcxhr_mgr {int fw_file_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCXHR_DRIVER_VERSION ; 
 int PCXHR_FIRMWARE_DSP_MAIN_INDEX ; 
 int /*<<< orphan*/  PCXHR_FIRMWARE_FILES_MAX_INDEX ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int pcxhr_hwdep_dsp_status(struct snd_hwdep *hw,
				  struct snd_hwdep_dsp_status *info)
{
	struct pcxhr_mgr *mgr = hw->private_data;
	sprintf(info->id, "pcxhr%d", mgr->fw_file_set);
        info->num_dsps = PCXHR_FIRMWARE_FILES_MAX_INDEX;

	if (hw->dsp_loaded & (1 << PCXHR_FIRMWARE_DSP_MAIN_INDEX))
		info->chip_ready = 1;

	info->version = PCXHR_DRIVER_VERSION;
	return 0;
}