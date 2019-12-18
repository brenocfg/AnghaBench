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
struct snd_timer_id {int card; int device; int subdevice; int /*<<< orphan*/  dev_sclass; int /*<<< orphan*/  dev_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_TIMER_CLASS_NONE ; 
 int /*<<< orphan*/  SNDRV_TIMER_SCLASS_NONE ; 

__attribute__((used)) static void snd_timer_user_zero_id(struct snd_timer_id *id)
{
	id->dev_class = SNDRV_TIMER_CLASS_NONE;
	id->dev_sclass = SNDRV_TIMER_SCLASS_NONE;
	id->card = -1;
	id->device = -1;
	id->subdevice = -1;
}