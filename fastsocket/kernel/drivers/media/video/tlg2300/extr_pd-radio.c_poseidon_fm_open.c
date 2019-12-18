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
struct video_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ pre_emphasis; int /*<<< orphan*/  users; } ;
struct poseidon {int state; int /*<<< orphan*/  lock; int /*<<< orphan*/  kref; TYPE_1__ radio_data; int /*<<< orphan*/  interface; } ;
struct file {struct poseidon* private_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int POSEIDON_STATE_DISCONNECT ; 
 int POSEIDON_STATE_FM ; 
 scalar_t__ TLG_TUNE_ASTD_FM_EUR ; 
 int /*<<< orphan*/  debug_mode ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int poseidon_check_mode_radio (struct poseidon*) ; 
 int /*<<< orphan*/  set_debug_mode (struct video_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 
 struct video_device* video_devdata (struct file*) ; 
 struct poseidon* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static int poseidon_fm_open(struct file *filp)
{
	struct video_device *vfd = video_devdata(filp);
	struct poseidon *p = video_get_drvdata(vfd);
	int ret = 0;

	if (!p)
		return -1;

	mutex_lock(&p->lock);
	if (p->state & POSEIDON_STATE_DISCONNECT) {
		ret = -ENODEV;
		goto out;
	}

	if (p->state && !(p->state & POSEIDON_STATE_FM)) {
		ret = -EBUSY;
		goto out;
	}

	usb_autopm_get_interface(p->interface);
	if (0 == p->state) {
		/* default pre-emphasis */
		if (p->radio_data.pre_emphasis == 0)
			p->radio_data.pre_emphasis = TLG_TUNE_ASTD_FM_EUR;
		set_debug_mode(vfd, debug_mode);

		ret = poseidon_check_mode_radio(p);
		if (ret < 0) {
			usb_autopm_put_interface(p->interface);
			goto out;
		}
		p->state |= POSEIDON_STATE_FM;
	}
	p->radio_data.users++;
	kref_get(&p->kref);
	filp->private_data = p;
out:
	mutex_unlock(&p->lock);
	return ret;
}