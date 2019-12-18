#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* mix; } ;
typedef  TYPE_2__ wavnc_info ;
struct TYPE_6__ {int stereo_devs; int (* decode_mixer ) (TYPE_2__*,int,unsigned int,unsigned int) ;} ;

/* Variables and functions */
 int stub1 (TYPE_2__*,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  waveartist_mixer_update (TYPE_2__*,int) ; 

__attribute__((used)) static int
waveartist_set_mixer(wavnc_info *devc, int dev, unsigned int level)
{
	unsigned int lev_left  = level & 0x00ff;
	unsigned int lev_right = (level & 0xff00) >> 8;

	if (lev_left > 100)
		lev_left = 100;
	if (lev_right > 100)
		lev_right = 100;

	/*
	 * Mono devices have their right volume forced to their
	 * left volume.  (from ALSA driver OSS emulation).
	 */
	if (!(devc->mix->stereo_devs & (1 << dev)))
		lev_right = lev_left;

	dev = devc->mix->decode_mixer(devc, dev, lev_left, lev_right);

	if (dev >= 0)
		waveartist_mixer_update(devc, dev);

	return dev < 0 ? dev : 0;
}