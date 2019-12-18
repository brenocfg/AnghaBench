#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_opl4 {TYPE_1__* chset; } ;
struct opl4_voice {size_t velocity; int level_direct; scalar_t__ number; TYPE_3__* sound; TYPE_2__* chan; } ;
struct TYPE_6__ {int tone_attenuate; int volume_factor; } ;
struct TYPE_5__ {int gm_volume; int gm_expression; } ;
struct TYPE_4__ {int gs_master_volume; } ;

/* Variables and functions */
 scalar_t__ OPL4_REG_LEVEL ; 
 scalar_t__* snd_opl4_volume_table ; 
 int /*<<< orphan*/  snd_opl4_write (struct snd_opl4*,scalar_t__,int) ; 
 int volume_boost ; 

__attribute__((used)) static void snd_opl4_update_volume(struct snd_opl4 *opl4, struct opl4_voice *voice)
{
	int att;

	att = voice->sound->tone_attenuate;
	att += snd_opl4_volume_table[opl4->chset->gs_master_volume & 0x7f];
	att += snd_opl4_volume_table[voice->chan->gm_volume & 0x7f];
	att += snd_opl4_volume_table[voice->chan->gm_expression & 0x7f];
	att += snd_opl4_volume_table[voice->velocity];
	att = 0x7f - (0x7f - att) * (voice->sound->volume_factor) / 0xfe - volume_boost;
	if (att < 0)
		att = 0;
	else if (att > 0x7e)
		att = 0x7e;
	snd_opl4_write(opl4, OPL4_REG_LEVEL + voice->number,
		       (att << 1) | voice->level_direct);
	voice->level_direct = 0;
}