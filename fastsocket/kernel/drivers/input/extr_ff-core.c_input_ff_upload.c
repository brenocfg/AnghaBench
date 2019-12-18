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
struct input_dev {int /*<<< orphan*/  event_lock; int /*<<< orphan*/  ffbit; int /*<<< orphan*/  evbit; struct ff_device* ff; } ;
struct file {int dummy; } ;
struct TYPE_3__ {scalar_t__ waveform; } ;
struct TYPE_4__ {TYPE_1__ periodic; } ;
struct ff_effect {scalar_t__ type; int id; TYPE_2__ u; } ;
struct ff_device {int max_effects; int (* upload ) (struct input_dev*,struct ff_effect*,struct ff_effect*) ;int /*<<< orphan*/  mutex; struct file** effect_owners; struct ff_effect* effects; int /*<<< orphan*/  ffbit; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 int ENOSYS ; 
 scalar_t__ EV_FF ; 
 scalar_t__ FF_EFFECT_MAX ; 
 scalar_t__ FF_EFFECT_MIN ; 
 scalar_t__ FF_PERIODIC ; 
 scalar_t__ FF_WAVEFORM_MAX ; 
 scalar_t__ FF_WAVEFORM_MIN ; 
 int check_effect_access (struct ff_device*,int,struct file*) ; 
 int /*<<< orphan*/  check_effects_compatible (struct ff_effect*,struct ff_effect*) ; 
 int compat_effect (struct ff_device*,struct ff_effect*) ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int stub1 (struct input_dev*,struct ff_effect*,struct ff_effect*) ; 
 int /*<<< orphan*/  test_bit (scalar_t__,int /*<<< orphan*/ ) ; 

int input_ff_upload(struct input_dev *dev, struct ff_effect *effect,
		    struct file *file)
{
	struct ff_device *ff = dev->ff;
	struct ff_effect *old;
	int ret = 0;
	int id;

	if (!test_bit(EV_FF, dev->evbit))
		return -ENOSYS;

	if (effect->type < FF_EFFECT_MIN || effect->type > FF_EFFECT_MAX ||
	    !test_bit(effect->type, dev->ffbit)) {
		debug("invalid or not supported effect type in upload");
		return -EINVAL;
	}

	if (effect->type == FF_PERIODIC &&
	    (effect->u.periodic.waveform < FF_WAVEFORM_MIN ||
	     effect->u.periodic.waveform > FF_WAVEFORM_MAX ||
	     !test_bit(effect->u.periodic.waveform, dev->ffbit))) {
		debug("invalid or not supported wave form in upload");
		return -EINVAL;
	}

	if (!test_bit(effect->type, ff->ffbit)) {
		ret = compat_effect(ff, effect);
		if (ret)
			return ret;
	}

	mutex_lock(&ff->mutex);

	if (effect->id == -1) {
		for (id = 0; id < ff->max_effects; id++)
		     if (!ff->effect_owners[id])
			break;

		if (id >= ff->max_effects) {
			ret = -ENOSPC;
			goto out;
		}

		effect->id = id;
		old = NULL;

	} else {
		id = effect->id;

		ret = check_effect_access(ff, id, file);
		if (ret)
			goto out;

		old = &ff->effects[id];

		if (!check_effects_compatible(effect, old)) {
			ret = -EINVAL;
			goto out;
		}
	}

	ret = ff->upload(dev, effect, old);
	if (ret)
		goto out;

	spin_lock_irq(&dev->event_lock);
	ff->effects[id] = *effect;
	ff->effect_owners[id] = file;
	spin_unlock_irq(&dev->event_lock);

 out:
	mutex_unlock(&ff->mutex);
	return ret;
}