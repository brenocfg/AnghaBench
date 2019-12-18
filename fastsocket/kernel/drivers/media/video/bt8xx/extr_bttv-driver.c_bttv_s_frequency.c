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
struct v4l2_frequency {scalar_t__ tuner; scalar_t__ type; int /*<<< orphan*/  frequency; } ;
struct file {int dummy; } ;
struct bttv_fh {int /*<<< orphan*/  prio; struct bttv* btv; } ;
struct bttv {int /*<<< orphan*/  freq; scalar_t__ radio_user; scalar_t__ has_matchbox; int /*<<< orphan*/  prio; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_TUNER_ANALOG_TV ; 
 scalar_t__ V4L2_TUNER_RADIO ; 
 int /*<<< orphan*/  bttv_call_all (struct bttv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_frequency*) ; 
 int /*<<< orphan*/  s_frequency ; 
 int /*<<< orphan*/  tea5757_set_freq (struct bttv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuner ; 
 scalar_t__ unlikely (int) ; 
 int v4l2_prio_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bttv_s_frequency(struct file *file, void *priv,
					struct v4l2_frequency *f)
{
	struct bttv_fh *fh  = priv;
	struct bttv *btv = fh->btv;
	int err;

	if (unlikely(f->tuner != 0))
		return -EINVAL;

	err = v4l2_prio_check(&btv->prio, fh->prio);
	if (unlikely(err))
		goto err;

	if (unlikely(f->type != (btv->radio_user
		? V4L2_TUNER_RADIO : V4L2_TUNER_ANALOG_TV))) {
		err = -EINVAL;
		goto err;
	}
	btv->freq = f->frequency;
	bttv_call_all(btv, tuner, s_frequency, f);
	if (btv->has_matchbox && btv->radio_user)
		tea5757_set_freq(btv, btv->freq);
err:

	return 0;
}