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
struct v4l2_tuner {scalar_t__ index; int rangelow; int rangehigh; int signal; scalar_t__ afc; int /*<<< orphan*/  audmode; int /*<<< orphan*/  rxsubchans; int /*<<< orphan*/  capability; int /*<<< orphan*/  type; } ;
struct tuner_fm_sig_stat_s {int sig_strength; scalar_t__ sig_locked; scalar_t__ sig_present; scalar_t__ sig_lock_busy; } ;
struct poseidon {int /*<<< orphan*/  lock; } ;
struct file {struct poseidon* private_data; } ;
typedef  int /*<<< orphan*/  fm_stat ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TLG_MODE_FM_RADIO ; 
 int TUNER_FREQ_MAX_FM ; 
 int TUNER_FREQ_MIN_FM ; 
 int /*<<< orphan*/  TUNER_STATUS ; 
 int /*<<< orphan*/  V4L2_TUNER_CAP_STEREO ; 
 int /*<<< orphan*/  V4L2_TUNER_MODE_STEREO ; 
 int /*<<< orphan*/  V4L2_TUNER_RADIO ; 
 int /*<<< orphan*/  V4L2_TUNER_SUB_STEREO ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 
 int send_get_req (struct poseidon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tuner_fm_sig_stat_s*,int*,int) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tlg_fm_vidioc_g_tuner(struct file *file, void *priv,
				 struct v4l2_tuner *vt)
{
	struct tuner_fm_sig_stat_s fm_stat = {};
	int ret, status, count = 5;
	struct poseidon *p = file->private_data;

	if (vt->index != 0)
		return -EINVAL;

	vt->type	= V4L2_TUNER_RADIO;
	vt->capability	= V4L2_TUNER_CAP_STEREO;
	vt->rangelow	= TUNER_FREQ_MIN_FM / 62500;
	vt->rangehigh	= TUNER_FREQ_MAX_FM / 62500;
	vt->rxsubchans	= V4L2_TUNER_SUB_STEREO;
	vt->audmode	= V4L2_TUNER_MODE_STEREO;
	vt->signal	= 0;
	vt->afc 	= 0;

	mutex_lock(&p->lock);
	ret = send_get_req(p, TUNER_STATUS, TLG_MODE_FM_RADIO,
			      &fm_stat, &status, sizeof(fm_stat));

	while (fm_stat.sig_lock_busy && count-- && !ret) {
		set_current_state(TASK_INTERRUPTIBLE);
		schedule_timeout(HZ);

		ret = send_get_req(p, TUNER_STATUS, TLG_MODE_FM_RADIO,
				  &fm_stat, &status, sizeof(fm_stat));
	}
	mutex_unlock(&p->lock);

	if (ret || status) {
		vt->signal = 0;
	} else if ((fm_stat.sig_present || fm_stat.sig_locked)
			&& fm_stat.sig_strength == 0) {
		vt->signal = 0xffff;
	} else
		vt->signal = (fm_stat.sig_strength * 255 / 10) << 8;

	return 0;
}