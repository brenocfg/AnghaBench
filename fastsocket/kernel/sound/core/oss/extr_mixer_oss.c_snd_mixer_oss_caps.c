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
struct snd_mixer_oss_file {struct snd_mixer_oss* mixer; } ;
struct snd_mixer_oss {scalar_t__ put_recsrc; scalar_t__ get_recsrc; } ;

/* Variables and functions */
 int EIO ; 
 int SOUND_CAP_EXCL_INPUT ; 

__attribute__((used)) static int snd_mixer_oss_caps(struct snd_mixer_oss_file *fmixer)
{
	struct snd_mixer_oss *mixer = fmixer->mixer;
	int result = 0;

	if (mixer == NULL)
		return -EIO;
	if (mixer->get_recsrc && mixer->put_recsrc)
		result |= SOUND_CAP_EXCL_INPUT;
	return result;
}