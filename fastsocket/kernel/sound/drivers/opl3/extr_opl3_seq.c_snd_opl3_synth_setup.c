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
struct snd_opl3 {int connection_reg; scalar_t__ hardware; int max_voices; int /*<<< orphan*/  (* command ) (struct snd_opl3*,int,int) ;scalar_t__ use_time; TYPE_1__* voices; struct snd_hwdep* hwdep; } ;
struct snd_hwdep {int /*<<< orphan*/  open_mutex; scalar_t__ used; } ;
struct TYPE_2__ {int keyon_reg; scalar_t__ time; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int EBUSY ; 
 int MAX_OPL3_VOICES ; 
 scalar_t__ OPL3_HW_OPL3 ; 
 int OPL3_REG_CONNECTION_SELECT ; 
 int OPL3_RIGHT ; 
 int /*<<< orphan*/  SNDRV_OPL3_ST_OFF ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_opl3_reset (struct snd_opl3*) ; 
 int /*<<< orphan*/  stub1 (struct snd_opl3*,int,int) ; 

int snd_opl3_synth_setup(struct snd_opl3 * opl3)
{
	int idx;
	struct snd_hwdep *hwdep = opl3->hwdep;

	mutex_lock(&hwdep->open_mutex);
	if (hwdep->used) {
		mutex_unlock(&hwdep->open_mutex);
		return -EBUSY;
	}
	hwdep->used++;
	mutex_unlock(&hwdep->open_mutex);

	snd_opl3_reset(opl3);

	for (idx = 0; idx < MAX_OPL3_VOICES; idx++) {
		opl3->voices[idx].state = SNDRV_OPL3_ST_OFF;
		opl3->voices[idx].time = 0;
		opl3->voices[idx].keyon_reg = 0x00;
	}
	opl3->use_time = 0;
	opl3->connection_reg = 0x00;
	if (opl3->hardware >= OPL3_HW_OPL3) {
		/* Clear 4-op connections */
		opl3->command(opl3, OPL3_RIGHT | OPL3_REG_CONNECTION_SELECT,
				 opl3->connection_reg);
		opl3->max_voices = MAX_OPL3_VOICES;
	}
	return 0;
}