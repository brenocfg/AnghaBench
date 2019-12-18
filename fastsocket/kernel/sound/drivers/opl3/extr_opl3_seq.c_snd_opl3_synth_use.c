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
struct TYPE_4__ {scalar_t__ client; } ;
struct snd_seq_port_subscribe {TYPE_2__ sender; } ;
struct snd_opl3 {int drum_reg; int /*<<< orphan*/  synth_mode; int /*<<< orphan*/  (* command ) (struct snd_opl3*,int,int) ;TYPE_1__* voices; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int OPL3_LEFT ; 
 int OPL3_PERCUSSION_ENABLE ; 
 int OPL3_REG_PERCUSSION ; 
 int /*<<< orphan*/  SNDRV_OPL3_MODE_SEQ ; 
 int /*<<< orphan*/  SNDRV_OPL3_ST_NOT_AVAIL ; 
 scalar_t__ SNDRV_SEQ_CLIENT_SYSTEM ; 
 int /*<<< orphan*/  snd_opl3_load_drums (struct snd_opl3*) ; 
 int snd_opl3_synth_setup (struct snd_opl3*) ; 
 int snd_opl3_synth_use_inc (struct snd_opl3*) ; 
 int /*<<< orphan*/  stub1 (struct snd_opl3*,int,int) ; 
 scalar_t__ use_internal_drums ; 

__attribute__((used)) static int snd_opl3_synth_use(void *private_data, struct snd_seq_port_subscribe * info)
{
	struct snd_opl3 *opl3 = private_data;
	int err;

	if ((err = snd_opl3_synth_setup(opl3)) < 0)
		return err;

	if (use_internal_drums) {
		/* Percussion mode */
		opl3->voices[6].state = opl3->voices[7].state = 
			opl3->voices[8].state = SNDRV_OPL3_ST_NOT_AVAIL;
		snd_opl3_load_drums(opl3);
		opl3->drum_reg = OPL3_PERCUSSION_ENABLE;
		opl3->command(opl3, OPL3_LEFT | OPL3_REG_PERCUSSION, opl3->drum_reg);
	} else {
		opl3->drum_reg = 0x00;
	}

	if (info->sender.client != SNDRV_SEQ_CLIENT_SYSTEM) {
		if ((err = snd_opl3_synth_use_inc(opl3)) < 0)
			return err;
	}
	opl3->synth_mode = SNDRV_OPL3_MODE_SEQ;
	return 0;
}