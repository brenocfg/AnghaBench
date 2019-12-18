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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_8__ {int threshold; int gain; int attack_time; int enabled; int release_time; } ;
struct TYPE_7__ {int deviation; int enabled; int release_time; } ;
struct TYPE_6__ {int frequency; int deviation; int enabled; } ;
struct TYPE_5__ {int pi; int deviation; int pty; } ;
struct si4713_device {int preemphasis; TYPE_4__ acomp_info; TYPE_3__ limiter_info; TYPE_2__ pilot_info; TYPE_1__ rds_info; } ;
typedef  int s32 ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned long*) ; 
 int ATTACK_TIME_UNIT ; 
 int EINVAL ; 
 int /*<<< orphan*/  SI4713_TX_ACOMP_ATTACK_TIME ; 
 int /*<<< orphan*/  SI4713_TX_ACOMP_ENABLE ; 
 int /*<<< orphan*/  SI4713_TX_ACOMP_GAIN ; 
 int /*<<< orphan*/  SI4713_TX_ACOMP_RELEASE_TIME ; 
 int /*<<< orphan*/  SI4713_TX_ACOMP_THRESHOLD ; 
 int /*<<< orphan*/  SI4713_TX_AUDIO_DEVIATION ; 
 int /*<<< orphan*/  SI4713_TX_COMPONENT_ENABLE ; 
 int /*<<< orphan*/  SI4713_TX_LIMITER_RELEASE_TIME ; 
 int /*<<< orphan*/  SI4713_TX_PILOT_DEVIATION ; 
 int /*<<< orphan*/  SI4713_TX_PILOT_FREQUENCY ; 
 int /*<<< orphan*/  SI4713_TX_PREEMPHASIS ; 
 int /*<<< orphan*/  SI4713_TX_RDS_DEVIATION ; 
 int /*<<< orphan*/  SI4713_TX_RDS_PI ; 
 int /*<<< orphan*/  SI4713_TX_RDS_PS_MISC ; 
#define  V4L2_CID_AUDIO_COMPRESSION_ATTACK_TIME 142 
#define  V4L2_CID_AUDIO_COMPRESSION_ENABLED 141 
#define  V4L2_CID_AUDIO_COMPRESSION_GAIN 140 
#define  V4L2_CID_AUDIO_COMPRESSION_RELEASE_TIME 139 
#define  V4L2_CID_AUDIO_COMPRESSION_THRESHOLD 138 
#define  V4L2_CID_AUDIO_LIMITER_DEVIATION 137 
#define  V4L2_CID_AUDIO_LIMITER_ENABLED 136 
#define  V4L2_CID_AUDIO_LIMITER_RELEASE_TIME 135 
#define  V4L2_CID_PILOT_TONE_DEVIATION 134 
#define  V4L2_CID_PILOT_TONE_ENABLED 133 
#define  V4L2_CID_PILOT_TONE_FREQUENCY 132 
#define  V4L2_CID_RDS_TX_DEVIATION 131 
#define  V4L2_CID_RDS_TX_PI 130 
#define  V4L2_CID_RDS_TX_PTY 129 
#define  V4L2_CID_TUNE_PREEMPHASIS 128 
 unsigned long* acomp_rtimes ; 
 unsigned long* limiter_times ; 
 unsigned long* preemphasis_values ; 

__attribute__((used)) static int si4713_choose_econtrol_action(struct si4713_device *sdev, u32 id,
		u32 **shadow, s32 *bit, s32 *mask, u16 *property, int *mul,
		unsigned long **table, int *size)
{
	s32 rval = 0;

	switch (id) {
	/* FM_TX class controls */
	case V4L2_CID_RDS_TX_PI:
		*property = SI4713_TX_RDS_PI;
		*mul = 1;
		*shadow = &sdev->rds_info.pi;
		break;
	case V4L2_CID_AUDIO_COMPRESSION_THRESHOLD:
		*property = SI4713_TX_ACOMP_THRESHOLD;
		*mul = 1;
		*shadow = &sdev->acomp_info.threshold;
		break;
	case V4L2_CID_AUDIO_COMPRESSION_GAIN:
		*property = SI4713_TX_ACOMP_GAIN;
		*mul = 1;
		*shadow = &sdev->acomp_info.gain;
		break;
	case V4L2_CID_PILOT_TONE_FREQUENCY:
		*property = SI4713_TX_PILOT_FREQUENCY;
		*mul = 1;
		*shadow = &sdev->pilot_info.frequency;
		break;
	case V4L2_CID_AUDIO_COMPRESSION_ATTACK_TIME:
		*property = SI4713_TX_ACOMP_ATTACK_TIME;
		*mul = ATTACK_TIME_UNIT;
		*shadow = &sdev->acomp_info.attack_time;
		break;
	case V4L2_CID_PILOT_TONE_DEVIATION:
		*property = SI4713_TX_PILOT_DEVIATION;
		*mul = 10;
		*shadow = &sdev->pilot_info.deviation;
		break;
	case V4L2_CID_AUDIO_LIMITER_DEVIATION:
		*property = SI4713_TX_AUDIO_DEVIATION;
		*mul = 10;
		*shadow = &sdev->limiter_info.deviation;
		break;
	case V4L2_CID_RDS_TX_DEVIATION:
		*property = SI4713_TX_RDS_DEVIATION;
		*mul = 1;
		*shadow = &sdev->rds_info.deviation;
		break;

	case V4L2_CID_RDS_TX_PTY:
		*property = SI4713_TX_RDS_PS_MISC;
		*bit = 5;
		*mask = 0x1F << 5;
		*shadow = &sdev->rds_info.pty;
		break;
	case V4L2_CID_AUDIO_LIMITER_ENABLED:
		*property = SI4713_TX_ACOMP_ENABLE;
		*bit = 1;
		*mask = 1 << 1;
		*shadow = &sdev->limiter_info.enabled;
		break;
	case V4L2_CID_AUDIO_COMPRESSION_ENABLED:
		*property = SI4713_TX_ACOMP_ENABLE;
		*bit = 0;
		*mask = 1 << 0;
		*shadow = &sdev->acomp_info.enabled;
		break;
	case V4L2_CID_PILOT_TONE_ENABLED:
		*property = SI4713_TX_COMPONENT_ENABLE;
		*bit = 0;
		*mask = 1 << 0;
		*shadow = &sdev->pilot_info.enabled;
		break;

	case V4L2_CID_AUDIO_LIMITER_RELEASE_TIME:
		*property = SI4713_TX_LIMITER_RELEASE_TIME;
		*table = limiter_times;
		*size = ARRAY_SIZE(limiter_times);
		*shadow = &sdev->limiter_info.release_time;
		break;
	case V4L2_CID_AUDIO_COMPRESSION_RELEASE_TIME:
		*property = SI4713_TX_ACOMP_RELEASE_TIME;
		*table = acomp_rtimes;
		*size = ARRAY_SIZE(acomp_rtimes);
		*shadow = &sdev->acomp_info.release_time;
		break;
	case V4L2_CID_TUNE_PREEMPHASIS:
		*property = SI4713_TX_PREEMPHASIS;
		*table = preemphasis_values;
		*size = ARRAY_SIZE(preemphasis_values);
		*shadow = &sdev->preemphasis;
		break;

	default:
		rval = -EINVAL;
	};

	return rval;
}