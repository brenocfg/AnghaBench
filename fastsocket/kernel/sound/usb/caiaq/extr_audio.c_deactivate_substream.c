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
struct snd_usb_caiaqdev {int /*<<< orphan*/  spinlock; int /*<<< orphan*/ ** sub_capture; int /*<<< orphan*/ ** sub_playback; } ;
struct snd_pcm_substream {scalar_t__ stream; size_t number; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
deactivate_substream(struct snd_usb_caiaqdev *dev,
		     struct snd_pcm_substream *sub)
{
	unsigned long flags;
	spin_lock_irqsave(&dev->spinlock, flags);

	if (sub->stream == SNDRV_PCM_STREAM_PLAYBACK)
		dev->sub_playback[sub->number] = NULL;
	else
		dev->sub_capture[sub->number] = NULL;

	spin_unlock_irqrestore(&dev->spinlock, flags);
}