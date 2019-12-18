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
struct snd_kcontrol {int dummy; } ;
struct snd_device {struct snd_card* device_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  next; } ;
struct snd_card {int /*<<< orphan*/  controls_rwsem; TYPE_1__ controls; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  snd_ctl_remove (struct snd_card*,struct snd_kcontrol*) ; 
 struct snd_kcontrol* snd_kcontrol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ctl_dev_free(struct snd_device *device)
{
	struct snd_card *card = device->device_data;
	struct snd_kcontrol *control;

	down_write(&card->controls_rwsem);
	while (!list_empty(&card->controls)) {
		control = snd_kcontrol(card->controls.next);
		snd_ctl_remove(card, control);
	}
	up_write(&card->controls_rwsem);
	return 0;
}