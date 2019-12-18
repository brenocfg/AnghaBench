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
typedef  int /*<<< orphan*/  u32 ;
struct cx88_core {int tvaudio; scalar_t__ last_change; } ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int /*<<< orphan*/  AUD_CTL ; 
 int EN_FMRADIO_EN_RDS ; 
 int /*<<< orphan*/  MO_AUD_DMACNTRL ; 
 int UNSET ; 
 int V4L2_TUNER_SUB_LANG2 ; 
 int V4L2_TUNER_SUB_MONO ; 
 int V4L2_TUNER_SUB_STEREO ; 
#define  WW_BG 138 
#define  WW_BTSC 137 
#define  WW_DK 136 
#define  WW_EIAJ 135 
#define  WW_FM 134 
#define  WW_I 133 
#define  WW_I2SADC 132 
#define  WW_I2SPT 131 
#define  WW_L 130 
#define  WW_M 129 
#define  WW_NONE 128 
 int cx_read (int /*<<< orphan*/ ) ; 
 int detect_a2_a2m_eiaj (struct cx88_core*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int detect_btsc (struct cx88_core*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (int,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/ * read_rds_samples (struct cx88_core*,int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,scalar_t__) ; 

s32 cx88_dsp_detect_stereo_sap(struct cx88_core *core)
{
	s16 *samples;
	u32 N = 0;
	s32 ret = UNSET;

	/* If audio RDS fifo is disabled, we can't read the samples */
	if (!(cx_read(MO_AUD_DMACNTRL) & 0x04))
		return ret;
	if (!(cx_read(AUD_CTL) & EN_FMRADIO_EN_RDS))
		return ret;

	/* Wait at least 500 ms after an audio standard change */
	if (time_before(jiffies, core->last_change + msecs_to_jiffies(500)))
		return ret;

	samples = read_rds_samples(core, &N);

	if (!samples)
		return ret;

	switch (core->tvaudio) {
	case WW_BG:
	case WW_DK:
	case WW_EIAJ:
	case WW_M:
		ret = detect_a2_a2m_eiaj(core, samples, N);
		break;
	case WW_BTSC:
		ret = detect_btsc(core, samples, N);
		break;
	case WW_NONE:
	case WW_I:
	case WW_L:
	case WW_I2SPT:
	case WW_FM:
	case WW_I2SADC:
		break;
	}

	kfree(samples);

	if (UNSET != ret)
		dprintk(1, "stereo/sap detection result:%s%s%s\n",
			   (ret & V4L2_TUNER_SUB_MONO) ? " mono" : "",
			   (ret & V4L2_TUNER_SUB_STEREO) ? " stereo" : "",
			   (ret & V4L2_TUNER_SUB_LANG2) ? " dual" : "");

	return ret;
}