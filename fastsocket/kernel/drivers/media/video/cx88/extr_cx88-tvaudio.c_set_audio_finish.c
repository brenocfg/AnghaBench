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
typedef  int u32 ;
struct TYPE_2__ {int mpeg; } ;
struct cx88_core {int /*<<< orphan*/  last_change; TYPE_1__ board; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUD_BAUDRATE ; 
 int /*<<< orphan*/  AUD_CTL ; 
 int /*<<< orphan*/  AUD_I2SCNTL ; 
 int /*<<< orphan*/  AUD_I2SINPUTCNTL ; 
 int /*<<< orphan*/  AUD_I2SOUTPUTCNTL ; 
 int /*<<< orphan*/  AUD_RATE_THRES_DMD ; 
 int /*<<< orphan*/  AUD_SOFT_RESET ; 
 int /*<<< orphan*/  AUD_VOL_CTL ; 
 int CX88_MPEG_BLACKBIRD ; 
 int EN_DAC_ENABLE ; 
 int /*<<< orphan*/  EN_I2SOUT_ENABLE ; 
 int /*<<< orphan*/  SHADOW_AUD_VOL_CTL ; 
 scalar_t__ always_analog ; 
 int /*<<< orphan*/  cx88_start_audio_dma (struct cx88_core*) ; 
 int /*<<< orphan*/  cx88_stop_audio_dma (struct cx88_core*) ; 
 int /*<<< orphan*/  cx_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cx_sread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_swrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static void set_audio_finish(struct cx88_core *core, u32 ctl)
{
	u32 volume;

	/* restart dma; This avoids buzz in NICAM and is good in others  */
	cx88_stop_audio_dma(core);
	cx_write(AUD_RATE_THRES_DMD, 0x000000C0);
	cx88_start_audio_dma(core);

	if (core->board.mpeg & CX88_MPEG_BLACKBIRD) {
		cx_write(AUD_I2SINPUTCNTL, 4);
		cx_write(AUD_BAUDRATE, 1);
		/* 'pass-thru mode': this enables the i2s output to the mpeg encoder */
		cx_set(AUD_CTL, EN_I2SOUT_ENABLE);
		cx_write(AUD_I2SOUTPUTCNTL, 1);
		cx_write(AUD_I2SCNTL, 0);
		/* cx_write(AUD_APB_IN_RATE_ADJ, 0); */
	}
	if ((always_analog) || (!(core->board.mpeg & CX88_MPEG_BLACKBIRD))) {
		ctl |= EN_DAC_ENABLE;
		cx_write(AUD_CTL, ctl);
	}

	/* finish programming */
	cx_write(AUD_SOFT_RESET, 0x0000);

	/* unmute */
	volume = cx_sread(SHADOW_AUD_VOL_CTL);
	cx_swrite(SHADOW_AUD_VOL_CTL, AUD_VOL_CTL, volume);

	core->last_change = jiffies;
}