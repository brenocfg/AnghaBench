#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct v4l2_modulator {int /*<<< orphan*/  txsubchans; scalar_t__ index; } ;
struct v4l2_frequency {scalar_t__ frequency; } ;
struct v4l2_ext_control {int /*<<< orphan*/  value; int /*<<< orphan*/  id; } ;
struct TYPE_8__ {scalar_t__ enabled; int /*<<< orphan*/  radio_text; int /*<<< orphan*/  ps_name; int /*<<< orphan*/  pty; int /*<<< orphan*/  deviation; int /*<<< orphan*/  pi; } ;
struct TYPE_7__ {int /*<<< orphan*/  release_time; int /*<<< orphan*/  enabled; int /*<<< orphan*/  attack_time; int /*<<< orphan*/  gain; int /*<<< orphan*/  threshold; } ;
struct TYPE_6__ {int /*<<< orphan*/  release_time; int /*<<< orphan*/  enabled; int /*<<< orphan*/  deviation; } ;
struct TYPE_5__ {int /*<<< orphan*/  enabled; int /*<<< orphan*/  deviation; int /*<<< orphan*/  frequency; } ;
struct si4713_device {int /*<<< orphan*/  sd; TYPE_4__ rds_info; scalar_t__ stereo; int /*<<< orphan*/  antenna_capacitor; int /*<<< orphan*/  power_level; scalar_t__ frequency; int /*<<< orphan*/  preemphasis; TYPE_3__ acomp_info; TYPE_2__ limiter_info; TYPE_1__ pilot_info; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 scalar_t__ DEFAULT_FREQUENCY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_COMPRESSION_ATTACK_TIME ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_COMPRESSION_ENABLED ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_COMPRESSION_GAIN ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_COMPRESSION_RELEASE_TIME ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_COMPRESSION_THRESHOLD ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_LIMITER_DEVIATION ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_LIMITER_ENABLED ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_LIMITER_RELEASE_TIME ; 
 int /*<<< orphan*/  V4L2_CID_PILOT_TONE_DEVIATION ; 
 int /*<<< orphan*/  V4L2_CID_PILOT_TONE_ENABLED ; 
 int /*<<< orphan*/  V4L2_CID_PILOT_TONE_FREQUENCY ; 
 int /*<<< orphan*/  V4L2_CID_RDS_TX_DEVIATION ; 
 int /*<<< orphan*/  V4L2_CID_RDS_TX_PI ; 
 int /*<<< orphan*/  V4L2_CID_RDS_TX_PS_NAME ; 
 int /*<<< orphan*/  V4L2_CID_RDS_TX_PTY ; 
 int /*<<< orphan*/  V4L2_CID_RDS_TX_RADIO_TEXT ; 
 int /*<<< orphan*/  V4L2_CID_TUNE_ANTENNA_CAPACITOR ; 
 int /*<<< orphan*/  V4L2_CID_TUNE_POWER_LEVEL ; 
 int /*<<< orphan*/  V4L2_CID_TUNE_PREEMPHASIS ; 
 int /*<<< orphan*/  V4L2_TUNER_SUB_MONO ; 
 int /*<<< orphan*/  V4L2_TUNER_SUB_RDS ; 
 int /*<<< orphan*/  V4L2_TUNER_SUB_STEREO ; 
 int /*<<< orphan*/  kfree (struct si4713_device*) ; 
 struct si4713_device* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct si4713_device*,struct si4713_device*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int si4713_s_frequency (int /*<<< orphan*/ *,struct v4l2_frequency*) ; 
 int /*<<< orphan*/  si4713_s_modulator (int /*<<< orphan*/ *,struct v4l2_modulator*) ; 
 int si4713_set_rds_ps_name (struct si4713_device*,int /*<<< orphan*/ ) ; 
 int si4713_set_rds_radio_text (struct si4713_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ si4713_to_v4l2 (scalar_t__) ; 
 int si4713_write_econtrol_integers (struct si4713_device*,struct v4l2_ext_control*) ; 
 int si4713_write_econtrol_tune (struct si4713_device*,struct v4l2_ext_control*) ; 

__attribute__((used)) static int si4713_setup(struct si4713_device *sdev)
{
	struct v4l2_ext_control ctrl;
	struct v4l2_frequency f;
	struct v4l2_modulator vm;
	struct si4713_device *tmp;
	int rval = 0;

	tmp = kmalloc(sizeof(*tmp), GFP_KERNEL);
	if (!tmp)
		return -ENOMEM;

	/* Get a local copy to avoid race */
	mutex_lock(&sdev->mutex);
	memcpy(tmp, sdev, sizeof(*sdev));
	mutex_unlock(&sdev->mutex);

	ctrl.id = V4L2_CID_RDS_TX_PI;
	ctrl.value = tmp->rds_info.pi;
	rval |= si4713_write_econtrol_integers(sdev, &ctrl);

	ctrl.id = V4L2_CID_AUDIO_COMPRESSION_THRESHOLD;
	ctrl.value = tmp->acomp_info.threshold;
	rval |= si4713_write_econtrol_integers(sdev, &ctrl);

	ctrl.id = V4L2_CID_AUDIO_COMPRESSION_GAIN;
	ctrl.value = tmp->acomp_info.gain;
	rval |= si4713_write_econtrol_integers(sdev, &ctrl);

	ctrl.id = V4L2_CID_PILOT_TONE_FREQUENCY;
	ctrl.value = tmp->pilot_info.frequency;
	rval |= si4713_write_econtrol_integers(sdev, &ctrl);

	ctrl.id = V4L2_CID_AUDIO_COMPRESSION_ATTACK_TIME;
	ctrl.value = tmp->acomp_info.attack_time;
	rval |= si4713_write_econtrol_integers(sdev, &ctrl);

	ctrl.id = V4L2_CID_PILOT_TONE_DEVIATION;
	ctrl.value = tmp->pilot_info.deviation;
	rval |= si4713_write_econtrol_integers(sdev, &ctrl);

	ctrl.id = V4L2_CID_AUDIO_LIMITER_DEVIATION;
	ctrl.value = tmp->limiter_info.deviation;
	rval |= si4713_write_econtrol_integers(sdev, &ctrl);

	ctrl.id = V4L2_CID_RDS_TX_DEVIATION;
	ctrl.value = tmp->rds_info.deviation;
	rval |= si4713_write_econtrol_integers(sdev, &ctrl);

	ctrl.id = V4L2_CID_RDS_TX_PTY;
	ctrl.value = tmp->rds_info.pty;
	rval |= si4713_write_econtrol_integers(sdev, &ctrl);

	ctrl.id = V4L2_CID_AUDIO_LIMITER_ENABLED;
	ctrl.value = tmp->limiter_info.enabled;
	rval |= si4713_write_econtrol_integers(sdev, &ctrl);

	ctrl.id = V4L2_CID_AUDIO_COMPRESSION_ENABLED;
	ctrl.value = tmp->acomp_info.enabled;
	rval |= si4713_write_econtrol_integers(sdev, &ctrl);

	ctrl.id = V4L2_CID_PILOT_TONE_ENABLED;
	ctrl.value = tmp->pilot_info.enabled;
	rval |= si4713_write_econtrol_integers(sdev, &ctrl);

	ctrl.id = V4L2_CID_AUDIO_LIMITER_RELEASE_TIME;
	ctrl.value = tmp->limiter_info.release_time;
	rval |= si4713_write_econtrol_integers(sdev, &ctrl);

	ctrl.id = V4L2_CID_AUDIO_COMPRESSION_RELEASE_TIME;
	ctrl.value = tmp->acomp_info.release_time;
	rval |= si4713_write_econtrol_integers(sdev, &ctrl);

	ctrl.id = V4L2_CID_TUNE_PREEMPHASIS;
	ctrl.value = tmp->preemphasis;
	rval |= si4713_write_econtrol_integers(sdev, &ctrl);

	ctrl.id = V4L2_CID_RDS_TX_PS_NAME;
	rval |= si4713_set_rds_ps_name(sdev, tmp->rds_info.ps_name);

	ctrl.id = V4L2_CID_RDS_TX_RADIO_TEXT;
	rval |= si4713_set_rds_radio_text(sdev, tmp->rds_info.radio_text);

	/* Device procedure needs to set frequency first */
	f.frequency = tmp->frequency ? tmp->frequency : DEFAULT_FREQUENCY;
	f.frequency = si4713_to_v4l2(f.frequency);
	rval |= si4713_s_frequency(&sdev->sd, &f);

	ctrl.id = V4L2_CID_TUNE_POWER_LEVEL;
	ctrl.value = tmp->power_level;
	rval |= si4713_write_econtrol_tune(sdev, &ctrl);

	ctrl.id = V4L2_CID_TUNE_ANTENNA_CAPACITOR;
	ctrl.value = tmp->antenna_capacitor;
	rval |= si4713_write_econtrol_tune(sdev, &ctrl);

	vm.index = 0;
	if (tmp->stereo)
		vm.txsubchans = V4L2_TUNER_SUB_STEREO;
	else
		vm.txsubchans = V4L2_TUNER_SUB_MONO;
	if (tmp->rds_info.enabled)
		vm.txsubchans |= V4L2_TUNER_SUB_RDS;
	si4713_s_modulator(&sdev->sd, &vm);

	kfree(tmp);

	return rval;
}