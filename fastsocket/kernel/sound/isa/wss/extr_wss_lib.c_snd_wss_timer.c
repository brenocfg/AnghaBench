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
struct snd_wss {struct snd_timer* timer; TYPE_1__* card; } ;
struct snd_timer_id {int device; scalar_t__ subdevice; int /*<<< orphan*/  card; int /*<<< orphan*/  dev_sclass; int /*<<< orphan*/  dev_class; } ;
struct snd_timer {int /*<<< orphan*/  hw; int /*<<< orphan*/  private_free; struct snd_wss* private_data; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_TIMER_CLASS_CARD ; 
 int /*<<< orphan*/  SNDRV_TIMER_SCLASS_NONE ; 
 int snd_timer_new (TYPE_1__*,char*,struct snd_timer_id*,struct snd_timer**) ; 
 int /*<<< orphan*/  snd_wss_chip_id (struct snd_wss*) ; 
 int /*<<< orphan*/  snd_wss_timer_free ; 
 int /*<<< orphan*/  snd_wss_timer_table ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int snd_wss_timer(struct snd_wss *chip, int device, struct snd_timer **rtimer)
{
	struct snd_timer *timer;
	struct snd_timer_id tid;
	int err;

	/* Timer initialization */
	tid.dev_class = SNDRV_TIMER_CLASS_CARD;
	tid.dev_sclass = SNDRV_TIMER_SCLASS_NONE;
	tid.card = chip->card->number;
	tid.device = device;
	tid.subdevice = 0;
	if ((err = snd_timer_new(chip->card, "CS4231", &tid, &timer)) < 0)
		return err;
	strcpy(timer->name, snd_wss_chip_id(chip));
	timer->private_data = chip;
	timer->private_free = snd_wss_timer_free;
	timer->hw = snd_wss_timer_table;
	chip->timer = timer;
	if (rtimer)
		*rtimer = timer;
	return 0;
}