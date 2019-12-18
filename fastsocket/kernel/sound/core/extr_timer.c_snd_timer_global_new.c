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
struct snd_timer_id {int card; int device; scalar_t__ subdevice; int /*<<< orphan*/  dev_sclass; int /*<<< orphan*/  dev_class; } ;
struct snd_timer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_TIMER_CLASS_GLOBAL ; 
 int /*<<< orphan*/  SNDRV_TIMER_SCLASS_NONE ; 
 int snd_timer_new (int /*<<< orphan*/ *,char*,struct snd_timer_id*,struct snd_timer**) ; 

int snd_timer_global_new(char *id, int device, struct snd_timer **rtimer)
{
	struct snd_timer_id tid;

	tid.dev_class = SNDRV_TIMER_CLASS_GLOBAL;
	tid.dev_sclass = SNDRV_TIMER_SCLASS_NONE;
	tid.card = -1;
	tid.device = device;
	tid.subdevice = 0;
	return snd_timer_new(NULL, id, &tid, rtimer);
}