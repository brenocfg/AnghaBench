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
struct snd_timer_id {int card; int /*<<< orphan*/  subdevice; int /*<<< orphan*/  device; int /*<<< orphan*/  dev_sclass; int /*<<< orphan*/  dev_class; } ;
struct snd_timer {int /*<<< orphan*/  tmr_subdevice; int /*<<< orphan*/  tmr_device; TYPE_1__* card; int /*<<< orphan*/  tmr_class; } ;
struct TYPE_2__ {int number; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_TIMER_SCLASS_NONE ; 

__attribute__((used)) static void snd_timer_user_copy_id(struct snd_timer_id *id, struct snd_timer *timer)
{
	id->dev_class = timer->tmr_class;
	id->dev_sclass = SNDRV_TIMER_SCLASS_NONE;
	id->card = timer->card ? timer->card->number : -1;
	id->device = timer->tmr_device;
	id->subdevice = timer->tmr_subdevice;
}