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
struct snd_wss {int dummy; } ;
struct snd_pcm {int /*<<< orphan*/  info_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_INFO_JOINT_DUPLEX ; 
 int snd_wss_pcm (struct snd_wss*,int,struct snd_pcm**) ; 

int snd_cs4236_pcm(struct snd_wss *chip, int device, struct snd_pcm **rpcm)
{
	struct snd_pcm *pcm;
	int err;
	
	err = snd_wss_pcm(chip, device, &pcm);
	if (err < 0)
		return err;
	pcm->info_flags &= ~SNDRV_PCM_INFO_JOINT_DUPLEX;
	if (rpcm)
		*rpcm = pcm;
	return 0;
}