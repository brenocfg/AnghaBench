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
struct snd_hwdep {struct snd_card* card; } ;
struct snd_card {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  chip_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  USX2Y_STAT_CHIP_MMAP_PCM_URBS ; 
 TYPE_1__* usX2Y (struct snd_card*) ; 
 int usX2Y_pcms_lock_check (struct snd_card*) ; 
 int /*<<< orphan*/  usX2Y_pcms_unlock (struct snd_card*) ; 

__attribute__((used)) static int snd_usX2Y_hwdep_pcm_open(struct snd_hwdep *hw, struct file *file)
{
	// we need to be the first 
	struct snd_card *card = hw->card;
	int err = usX2Y_pcms_lock_check(card);
	if (0 == err)
		usX2Y(card)->chip_status |= USX2Y_STAT_CHIP_MMAP_PCM_URBS;
	usX2Y_pcms_unlock(card);
	return err;
}