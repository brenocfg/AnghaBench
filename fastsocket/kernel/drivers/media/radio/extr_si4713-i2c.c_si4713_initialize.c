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
struct TYPE_8__ {int enabled; int /*<<< orphan*/  gain; int /*<<< orphan*/  threshold; int /*<<< orphan*/  attack_time; int /*<<< orphan*/  release_time; } ;
struct TYPE_7__ {int enabled; int /*<<< orphan*/  frequency; int /*<<< orphan*/  deviation; } ;
struct TYPE_6__ {int enabled; int /*<<< orphan*/  deviation; int /*<<< orphan*/  release_time; } ;
struct TYPE_5__ {int enabled; int /*<<< orphan*/  radio_text; int /*<<< orphan*/  ps_name; int /*<<< orphan*/  deviation; int /*<<< orphan*/  pty; int /*<<< orphan*/  pi; } ;
struct si4713_device {int stereo; int /*<<< orphan*/  mutex; int /*<<< orphan*/  tune_rnl; scalar_t__ antenna_capacitor; int /*<<< orphan*/  power_level; int /*<<< orphan*/  mute; int /*<<< orphan*/  preemphasis; int /*<<< orphan*/  frequency; TYPE_4__ acomp_info; TYPE_3__ pilot_info; TYPE_2__ limiter_info; TYPE_1__ rds_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_ACOMP_ATIME ; 
 int /*<<< orphan*/  DEFAULT_ACOMP_GAIN ; 
 int /*<<< orphan*/  DEFAULT_ACOMP_RTIME ; 
 int /*<<< orphan*/  DEFAULT_ACOMP_THRESHOLD ; 
 int /*<<< orphan*/  DEFAULT_FREQUENCY ; 
 int /*<<< orphan*/  DEFAULT_LIMITER_DEV ; 
 int /*<<< orphan*/  DEFAULT_LIMITER_RTIME ; 
 int /*<<< orphan*/  DEFAULT_MUTE ; 
 int /*<<< orphan*/  DEFAULT_PILOT_DEVIATION ; 
 int /*<<< orphan*/  DEFAULT_PILOT_FREQUENCY ; 
 int /*<<< orphan*/  DEFAULT_POWER_LEVEL ; 
 int /*<<< orphan*/  DEFAULT_PREEMPHASIS ; 
 int /*<<< orphan*/  DEFAULT_RDS_DEVIATION ; 
 int /*<<< orphan*/  DEFAULT_RDS_PI ; 
 int /*<<< orphan*/  DEFAULT_RDS_PS_NAME ; 
 int /*<<< orphan*/  DEFAULT_RDS_PTY ; 
 int /*<<< orphan*/  DEFAULT_RDS_RADIO_TEXT ; 
 int /*<<< orphan*/  DEFAULT_TUNE_RNL ; 
 int /*<<< orphan*/  MAX_RDS_PS_NAME ; 
 int /*<<< orphan*/  MAX_RDS_RADIO_TEXT ; 
 int /*<<< orphan*/  POWER_OFF ; 
 int /*<<< orphan*/  POWER_ON ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int si4713_checkrev (struct si4713_device*) ; 
 int si4713_set_power_state (struct si4713_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si4713_initialize(struct si4713_device *sdev)
{
	int rval;

	rval = si4713_set_power_state(sdev, POWER_ON);
	if (rval < 0)
		goto exit;

	rval = si4713_checkrev(sdev);
	if (rval < 0)
		goto exit;

	rval = si4713_set_power_state(sdev, POWER_OFF);
	if (rval < 0)
		goto exit;

	mutex_lock(&sdev->mutex);

	sdev->rds_info.pi = DEFAULT_RDS_PI;
	sdev->rds_info.pty = DEFAULT_RDS_PTY;
	sdev->rds_info.deviation = DEFAULT_RDS_DEVIATION;
	strlcpy(sdev->rds_info.ps_name, DEFAULT_RDS_PS_NAME, MAX_RDS_PS_NAME);
	strlcpy(sdev->rds_info.radio_text, DEFAULT_RDS_RADIO_TEXT,
							MAX_RDS_RADIO_TEXT);
	sdev->rds_info.enabled = 1;

	sdev->limiter_info.release_time = DEFAULT_LIMITER_RTIME;
	sdev->limiter_info.deviation = DEFAULT_LIMITER_DEV;
	sdev->limiter_info.enabled = 1;

	sdev->pilot_info.deviation = DEFAULT_PILOT_DEVIATION;
	sdev->pilot_info.frequency = DEFAULT_PILOT_FREQUENCY;
	sdev->pilot_info.enabled = 1;

	sdev->acomp_info.release_time = DEFAULT_ACOMP_RTIME;
	sdev->acomp_info.attack_time = DEFAULT_ACOMP_ATIME;
	sdev->acomp_info.threshold = DEFAULT_ACOMP_THRESHOLD;
	sdev->acomp_info.gain = DEFAULT_ACOMP_GAIN;
	sdev->acomp_info.enabled = 1;

	sdev->frequency = DEFAULT_FREQUENCY;
	sdev->preemphasis = DEFAULT_PREEMPHASIS;
	sdev->mute = DEFAULT_MUTE;
	sdev->power_level = DEFAULT_POWER_LEVEL;
	sdev->antenna_capacitor = 0;
	sdev->stereo = 1;
	sdev->tune_rnl = DEFAULT_TUNE_RNL;

	mutex_unlock(&sdev->mutex);

exit:
	return rval;
}