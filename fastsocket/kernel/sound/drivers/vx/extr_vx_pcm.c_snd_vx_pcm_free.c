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
struct vx_core {int /*<<< orphan*/ * capture_pipes; int /*<<< orphan*/ * playback_pipes; int /*<<< orphan*/ ** pcm; } ;
struct snd_pcm {size_t device; struct vx_core* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_vx_pcm_free(struct snd_pcm *pcm)
{
	struct vx_core *chip = pcm->private_data;
	chip->pcm[pcm->device] = NULL;
	kfree(chip->playback_pipes);
	chip->playback_pipes = NULL;
	kfree(chip->capture_pipes);
	chip->capture_pipes = NULL;
}