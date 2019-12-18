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
struct ac97_pcm {scalar_t__ stream; TYPE_1__* r; scalar_t__ spdif; } ;
struct TYPE_2__ {size_t* rate_table; } ;

/* Variables and functions */
 unsigned char AC97_SPDIF ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 unsigned char* rate_cregs ; 
 unsigned char*** rate_reg_tables ; 

__attribute__((used)) static unsigned char get_slot_reg(struct ac97_pcm *pcm, unsigned short cidx,
				  unsigned short slot, int dbl)
{
	if (slot < 3)
		return 0xff;
	if (slot > 11)
		return 0xff;
	if (pcm->spdif)
		return AC97_SPDIF; /* pseudo register */
	if (pcm->stream == SNDRV_PCM_STREAM_PLAYBACK)
		return rate_reg_tables[dbl][pcm->r[dbl].rate_table[cidx]][slot - 3];
	else
		return rate_cregs[slot - 3];
}