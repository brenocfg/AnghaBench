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
struct snd_emux_voice {int /*<<< orphan*/ * port; int /*<<< orphan*/ * chan; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* update ) (struct snd_emux_voice*,int) ;} ;
struct snd_emux {TYPE_1__ ops; } ;

/* Variables and functions */
 int SNDRV_EMUX_UPDATE_PAN ; 
 int SNDRV_EMUX_UPDATE_PITCH ; 
 int SNDRV_EMUX_UPDATE_VOLUME ; 
 int /*<<< orphan*/  STATE_IS_PLAYING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calc_pan (struct snd_emux_voice*) ; 
 int /*<<< orphan*/  calc_pitch (struct snd_emux_voice*) ; 
 int /*<<< orphan*/  calc_volume (struct snd_emux_voice*) ; 
 int /*<<< orphan*/  stub1 (struct snd_emux_voice*,int) ; 

__attribute__((used)) static void
update_voice(struct snd_emux *emu, struct snd_emux_voice *vp, int update)
{
	if (!STATE_IS_PLAYING(vp->state))
		return;

	if (vp->chan == NULL || vp->port == NULL)
		return;
	if (update & SNDRV_EMUX_UPDATE_VOLUME)
		calc_volume(vp);
	if (update & SNDRV_EMUX_UPDATE_PITCH)
		calc_pitch(vp);
	if (update & SNDRV_EMUX_UPDATE_PAN) {
		if (! calc_pan(vp) && (update == SNDRV_EMUX_UPDATE_PAN))
			return;
	}
	emu->ops.update(vp, update);
}