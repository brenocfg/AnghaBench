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
struct sonicvibes {int enable; int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int SNDRV_PCM_TRIGGER_START ; 
 int SNDRV_PCM_TRIGGER_STOP ; 
 int /*<<< orphan*/  SV_IREG_PC_ENABLE ; 
 int /*<<< orphan*/  snd_sonicvibes_out1 (struct sonicvibes*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_sonicvibes_trigger(struct sonicvibes * sonic, int what, int cmd)
{
	int result = 0;

	spin_lock(&sonic->reg_lock);
	if (cmd == SNDRV_PCM_TRIGGER_START) {
		if (!(sonic->enable & what)) {
			sonic->enable |= what;
			snd_sonicvibes_out1(sonic, SV_IREG_PC_ENABLE, sonic->enable);
		}
	} else if (cmd == SNDRV_PCM_TRIGGER_STOP) {
		if (sonic->enable & what) {
			sonic->enable &= ~what;
			snd_sonicvibes_out1(sonic, SV_IREG_PC_ENABLE, sonic->enable);
		}
	} else {
		result = -EINVAL;
	}
	spin_unlock(&sonic->reg_lock);
	return result;
}