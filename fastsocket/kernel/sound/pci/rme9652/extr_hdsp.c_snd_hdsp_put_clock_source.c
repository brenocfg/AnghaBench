#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {int dummy; } ;
struct TYPE_4__ {int* item; } ;
struct TYPE_3__ {TYPE_2__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;
struct hdsp {scalar_t__ io_type; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ H9632 ; 
 int hdsp_clock_source (struct hdsp*) ; 
 scalar_t__ hdsp_set_clock_source (struct hdsp*,int) ; 
 int /*<<< orphan*/  snd_hdsp_use_is_exclusive (struct hdsp*) ; 
 struct hdsp* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_hdsp_put_clock_source(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct hdsp *hdsp = snd_kcontrol_chip(kcontrol);
	int change;
	int val;

	if (!snd_hdsp_use_is_exclusive(hdsp))
		return -EBUSY;
	val = ucontrol->value.enumerated.item[0];
	if (val < 0) val = 0;
	if (hdsp->io_type == H9632) {
		if (val > 9)
			val = 9;
	} else {
		if (val > 6)
			val = 6;
	}
	spin_lock_irq(&hdsp->lock);
	if (val != hdsp_clock_source(hdsp))
		change = (hdsp_set_clock_source(hdsp, val) == 0) ? 1 : 0;
	else
		change = 0;
	spin_unlock_irq(&hdsp->lock);
	return change;
}